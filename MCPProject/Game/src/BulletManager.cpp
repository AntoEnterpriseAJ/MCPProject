#include "BulletManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <Game.h>

void BulletManager::addBullet(std::unique_ptr<Bullet> bullet)
{
    m_bullets.push_back(std::move(bullet));
    std::cout << m_bullets.size() << "\n";
}

void BulletManager::update(Level& level, float deltaTime)
{
    handleCollisions(level);

    for (auto& bullet : m_bullets)
    {
        auto* bulletPtr = static_cast<Bullet*>(bullet.get());
        bulletPtr->update(deltaTime);

        if (bulletPtr->getPosition().x < 0 || bulletPtr->getPosition().x > Game::getWindowWidth() ||
            bulletPtr->getPosition().y < 0 || bulletPtr->getPosition().y > Game::getWindowHeight())
        {
            bulletPtr->setState(Bullet::State::Inactive);
        }
    }

    for (auto& explosion : m_explosions)
    {
        auto* explosionPtr = static_cast<Explosion*>(explosion.get());
        explosionPtr->update(deltaTime);
    }
}

void BulletManager::handleCollisions(Level& level)
{
    auto& levelLayout = level.getBricks();

    for (auto& bullet : m_bullets)
    {
        auto* bulletPtr = static_cast<Bullet*>(bullet.get());
        if (!bulletPtr)
            continue;

        for (auto& object : levelLayout)
        {
            if (auto* brick = dynamic_cast<Brick*>(object.get()))
            {
                if (bulletPtr->getBounds().intersects(brick->getBounds()))
                {
                    bulletPtr->setState(Bullet::State::Inactive);
                    addExplosion(*bulletPtr);
                    brick->hit();

                    std::cout << "BRICK\n";
                }
            }
            else if (auto* bombBrick = dynamic_cast<BombBrick*>(object.get()))
            {
                if (bulletPtr->getBounds().intersects(bombBrick->getBounds()))
                {
                    bulletPtr->setState(Bullet::State::Inactive);
                    addExplosion(*bulletPtr);
                    detonate(bombBrick->getPosition(), level, bombBrick->GetExplosionRadius() * Obstacle::getObstacleSize());

                    std::cout << "BOMB\n";
                }
            }
            else if (auto* unbreakableBrick = dynamic_cast<UnbreakableBrick*>(object.get()))
            {
                if (bulletPtr->getBounds().intersects(unbreakableBrick->getBounds()))
                {
                    bulletPtr->setState(Bullet::State::Inactive);
                    addExplosion(*bulletPtr);

                    std::cout << "UNBREAKABLE BRICK\n";
                }
            }
            else if (auto* bush = dynamic_cast<Bush*>(object.get()))
            {
                if (bulletPtr->getBounds().intersects(bush->getBounds()))
                {
                    std::cout << "BUSH\n";
                }
            }
        }
    }

    removeInactive(level);
}

void BulletManager::detonate(const sf::Vector2f& bombPosition, Level& level, int radius)
{
    auto& levelLayout = level.getBricks();

    for (int index = 0; index < levelLayout.size(); ++index)
    {
        if (levelLayout[index] && levelLayout[index]->isDestroyable())
        {
            sf::Vector2f brickPosition = levelLayout[index]->getPosition();

            float distance = std::sqrt(
                std::pow(brickPosition.x - bombPosition.x, 2) +
                std::pow(brickPosition.y - bombPosition.y, 2)
            );

            if (distance <= radius)
            {
                levelLayout.erase(levelLayout.begin() + index);
                index--;
            }
        }
    }
}

void BulletManager::addExplosion(const Bullet& bullet)
{
    Direction direction = bullet.getDirection();
    sf::Vector2f explosionPos;

    switch (direction)
    {
        case Direction::Right:
            explosionPos = bullet.getPosition() + sf::Vector2f(bullet.getSize().x / 2.0f, 0);
            break;
        case Direction::Left:
            explosionPos = bullet.getPosition() - sf::Vector2f(bullet.getSize().x / 2.0f, 0);
            break;
        case Direction::Up:
            explosionPos = bullet.getPosition() - sf::Vector2f(0, bullet.getSize().y / 2.0f);
            break;
        case Direction::Down:
            explosionPos = bullet.getPosition() + sf::Vector2f(0, bullet.getSize().y / 2.0f);
            break;
    }

    m_explosions.emplace_back(std::make_unique<Explosion>(
        explosionPos, ResourceManager::getInstance().getTexture("explosionSheet")));
}

void BulletManager::removeInactive(Level& level)
{
    auto& levelLayout = level.getBricks();
    levelLayout.erase(
        std::remove_if(levelLayout.begin(), levelLayout.end(),
            [](const auto& obj) {
                if (auto* brick = dynamic_cast<Brick*>(obj.get()))
                {
                    return brick->isDestroyed();
                }
                return false;
            }),
        levelLayout.end());

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const auto& bullet) {
                auto* bulletPtr = dynamic_cast<Bullet*>(bullet.get());
                return bulletPtr && bulletPtr->getState() == Bullet::State::Inactive;
            }),
        m_bullets.end());

    m_explosions.erase(
        std::remove_if(m_explosions.begin(), m_explosions.end(),
            [](const auto& explosion) {
                auto* explosionPtr = dynamic_cast<Explosion*>(explosion.get());
                return explosionPtr && explosionPtr->hasFinished();
            }),
        m_explosions.end());
}

void BulletManager::draw(sf::RenderWindow& window) const
{
    for (const auto& bullet : m_bullets)
    {
        bullet->draw(window, {});
    }

    for (const auto& explosion : m_explosions)
    {
        explosion->draw(window, {});
    }
}
