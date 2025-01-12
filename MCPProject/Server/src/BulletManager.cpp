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

    for (auto& bullet : m_bullets)
    {
        int topLeftX = static_cast<int>(std::floor(bullet->getTopLeft().x / Level::kGridSize));
        int topLeftY = static_cast<int>(std::floor(bullet->getTopLeft().y / Level::kGridSize));
        int bottomRightX = static_cast<int>(std::floor(bullet->getBottomRight().x / Level::kGridSize));
        int bottomRightY = static_cast<int>(std::floor(bullet->getBottomRight().y / Level::kGridSize));

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
void BulletManager::detonate(const Vec2f& bombPosition, Level& level, int radius)
{
    auto& levelLayout = level.getLayout();

    int topLeftX     = static_cast<int>(std::floor((bombPosition.x - radius) / Level::kGridSize));
    int topLeftY     = static_cast<int>(std::floor((bombPosition.y - radius) / Level::kGridSize));
    int bottomRightX = static_cast<int>(std::floor((bombPosition.x + radius) / Level::kGridSize));
    int bottomRightY = static_cast<int>(std::floor((bombPosition.y + radius) / Level::kGridSize));

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

            if (auto brick = dynamic_cast<Brick*>(currentObstacle.get()) )
            {
                if (brick->isDestroyable())
                {
                    currentObstacle.reset();
                }
            }
            else if (auto bombBrick = dynamic_cast<BombBrick*>(currentObstacle.get()))
            {
                currentObstacle.reset();
            }
        }
    }
}

void BulletManager::removeInactive(Level& level)
{
    auto& levelLayout = level.getLayout();
    for (auto& obj : levelLayout)
    {
        if (obj == nullptr)
        {
            continue;
        }
        if (auto brick = dynamic_cast<Brick*>(obj.get()))
        {
            if (brick->isDestroyed())
            {
                obj.reset();
            }
        }
    }

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const auto& bullet) {
                auto* bulletPtr = dynamic_cast<Bullet*>(bullet.get());
                return bulletPtr && bulletPtr->getState() == Bullet::State::Inactive;
            }),
        m_bullets.end()
    );
}

const std::vector<std::unique_ptr<Bullet>>& BulletManager::getBullets() const noexcept
{
    return m_bullets;
}
