#include "BulletManager.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <Game.h>

void BulletManager::addExplosion(const Bullet& bullet)
{
    Direction direction = bullet.getDirection();
    sf::Vector2f explosionPos;

    switch (direction)
    {
        case Direction::Right:
            explosionPos = bullet.GetPosition() + sf::Vector2f(bullet.GetSize().x / 2.0f, 0);
            break;
        case Direction::Left:
            explosionPos = bullet.GetPosition() - sf::Vector2f(bullet.GetSize().x / 2.0f, 0);
            break;
        case Direction::Up:
            explosionPos = bullet.GetPosition() - sf::Vector2f(0, bullet.GetSize().y / 2.0f);
            break;
        case Direction::Down:
            explosionPos = bullet.GetPosition() + sf::Vector2f(0, bullet.GetSize().y / 2.0f);
            break;
    }

    m_explosions.emplace_back(std::make_unique<Explosion>(
        explosionPos, ResourceManager::getInstance().getTexture("explosionSheet"))
    );
}

void BulletManager::clearBullets() noexcept
{
    m_bullets.clear();
}

void BulletManager::addBullet(std::unique_ptr<Bullet> bullet)
{
    m_bullets.push_back(std::move(bullet));
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
