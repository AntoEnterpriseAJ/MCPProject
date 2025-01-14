#include "BulletManager.h"
#include "GameRoom.h"
#include "BombBrick.h"
#include "Brick.h"
#include "Bush.h"
#include "Vec2f.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <cmath>

void BulletManager::addBullet(std::unique_ptr<Bullet> bullet)
{
    m_bullets.push_back(std::move(bullet));
}

void BulletManager::update(Level& level, std::unordered_map<uint8_t, Player>& players, float deltaTime)
{
    handleCollisions(level, players);

    for (auto& bullet : m_bullets | std::views::filter([](const auto& b) { return b != nullptr; }))
    {
        bullet->update(deltaTime);
    }
}

void BulletManager::handleCollisions(Level& level, std::unordered_map<uint8_t, Player>& players)
{
    auto& levelLayout = level.getLayout();

    for (auto& bullet : m_bullets | std::views::filter([](const auto& b) { return b != nullptr; }))
    {
        auto [topLeftX, topLeftY]         = bullet->getTopLeft().toGridCoords(Level::kGridSize);
        auto [bottomRightX, bottomRightY] = bullet->getBottomRight().toGridCoords(Level::kGridSize);

        for (int x = topLeftX; x <= bottomRightX; ++x)
        {
            for (int y = topLeftY; y <= bottomRightY; ++y)
            {
                if (x < 0 || x >= Level::kWidth || y < 0 || y >= Level::kHeight)
                {
                    bullet->setState(Bullet::State::Inactive);
                    continue;
                }

                auto& currentObstacle{ level[{y, x}] };
                if (currentObstacle == nullptr)
                {
                    continue;
                }

                if (bullet->collides(*currentObstacle))
                {
                    if (auto brick = dynamic_cast<Brick*>(currentObstacle.get()))
                    {
                        if (brick->isDestroyable())
                        {
                            brick->hit();
                        }

                        bullet->setState(Bullet::State::Inactive);
                    }
                    else if (auto bombBrick = dynamic_cast<BombBrick*>(currentObstacle.get()))
                    {
                        std::cout << "Hit bomb brick\n";
                        bullet->setState(Bullet::State::Inactive);
                        detonate(bombBrick->GetPosition(), level, players);
                    }
                }
            }
        }
    }

    std::ranges::for_each(
        m_bullets | std::views::filter([](const auto& bullet) { return bullet && bullet->isActive(); }),
        [&](auto& bullet) {
            for (auto& other : m_bullets) {
                if (other && other->isActive() && other != bullet && bullet->collides(*other)) {
                    bullet->setState(Bullet::State::Inactive);
                    other->setState(Bullet::State::Inactive);
                    break;
                }
            }
        });

    handlePlayerCollision(players);

    removeInactive(level);
}

void BulletManager::handlePlayerCollision(std::unordered_map<uint8_t, Player>& players)
{
    auto isActiveBullet = [](const auto& bullet) {
        return bullet != nullptr && bullet->isActive();
        };

    auto isAlivePlayer = [](const Player& player) {
        return player.isAlive();
        };

    for (auto& bullet : m_bullets | std::views::filter(isActiveBullet))
    {
        for (auto& player : players | std::ranges::views::values | std::views::filter(isAlivePlayer))
        {
            if (bullet->collides(player))
            {
                player.hit(bullet->getDamage());
                bullet->setState(Bullet::State::Inactive);
                break;
            }
        }
    }
}

void BulletManager::detonate(const Vec2f& bombPosition, Level& level, std::unordered_map<uint8_t, Player>& players)
{
    auto& levelLayout          { level.getLayout() };
    constexpr float radius     { BombBrick::kExplosionRadius * Obstacle::kObstacleSize };
    Vec2f explosionTopLeft     { bombPosition - Vec2f{radius, radius} };
    Vec2f explosionBottomRight { bombPosition + Vec2f{radius, radius} };

    auto alivePlayers = players | std::views::values | std::views::filter([](const auto& player) {
        return player.isAlive(); 
        });

    auto [topLeftX, topLeftY]         = explosionTopLeft.toGridCoords(Level::kGridSize);
    auto [bottomRightX, bottomRightY] = explosionBottomRight.toGridCoords(Level::kGridSize);

    std::ranges::for_each(alivePlayers, [&](auto& player) {
        if (player.collides(explosionTopLeft, explosionBottomRight))
        {
            player.kill();
        }
        });

    for (int x = topLeftX; x <= bottomRightX; ++x)
    {
        for (int y = topLeftY; y <= bottomRightY; ++y)
        {
            if (x < 0 || x >= Level::kWidth || y < 0 || y >= Level::kHeight)
            {
                continue;
            }

            auto& currentObstacle{ level[{y, x}] };
            if (currentObstacle == nullptr)
            {
                continue;
            }

            if (auto brick = dynamic_cast<Brick*>(currentObstacle.get()); brick && !brick->isDestroyable())
            {
                continue;
            }
            else
            {
                currentObstacle.reset();
            }
        }
    }
}

void BulletManager::removeInactive(Level& level)
{
    auto& levelLayout = level.getLayout();
    for (auto& obj : levelLayout | std::views::filter([](const auto& o) { return o != nullptr; }))
    {
        if (auto brick = dynamic_cast<Brick*>(obj.get()); brick && brick->isDestroyed())
        {
            obj.reset();
        }
    }

    std::erase_if(m_bullets, [](const auto& bullet) {
        return bullet && bullet->getState() == Bullet::State::Inactive;
    });
}

const std::vector<std::unique_ptr<Bullet>>& BulletManager::getBullets() const noexcept
{
    return m_bullets;
}
