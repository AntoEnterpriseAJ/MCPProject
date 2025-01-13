#include "BulletManager.h"
#include "GameRoom.h"
#include "BombBrick.h"
#include "Brick.h"
#include "Bush.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <cmath>

void BulletManager::addBullet(std::unique_ptr<Bullet> bullet)
{
    m_bullets.push_back(std::move(bullet));
    std::cout << "Currently we have " << m_bullets.size() << " bullets\n";
}

void BulletManager::update(Level& level, float deltaTime)
{
    handleCollisions(level);

    for (auto& bullet : m_bullets)
    {
        bullet->update(deltaTime);
    }
}

void BulletManager::handleCollisions(Level& level)
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
                        detonate(bombBrick->GetPosition(), level, bombBrick->getExplosionRadius() * Obstacle::kObstacleSize);
                    }
                }
            }
        }
    }

    removeInactive(level);
}

// TODO: refactor
void BulletManager::detonate(const Vec2f& bombPosition, Level& level, float radius)
{
    auto& levelLayout = level.getLayout();

    auto [topLeftX, topLeftY]         = (bombPosition - Vec2f{radius, radius}).toGridCoords(Level::kGridSize);
    auto [bottomRightX, bottomRightY] = (bombPosition + Vec2f{radius, radius}).toGridCoords(Level::kGridSize);

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
