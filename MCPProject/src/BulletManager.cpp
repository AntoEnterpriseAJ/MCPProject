#include "BulletManager.h"
#include "Game.h"


#include <iostream>

void BulletManager::addBullet(const Bullet& bullet)
{
    m_bullets.push_back(bullet);
    std::cout << m_bullets.size() << "\n";
    std::cout << bullet.getSize().x << " " << bullet.getSize().y << "\n";
}

void BulletManager::update(std::vector<Brick>& level)
{
    handleCollisions(level);

    for (auto& bullet : m_bullets)
    {
        if (bullet.getDirection() == Direction::UP)
            bullet.move(0, -Bullet::kBulletSpeed);
        else if (bullet.getDirection() == Direction::DOWN)
            bullet.move(0, Bullet::kBulletSpeed);
        else if (bullet.getDirection() == Direction::LEFT)
            bullet.move(-Bullet::kBulletSpeed, 0);
        else if (bullet.getDirection() == Direction::RIGHT)
            bullet.move(Bullet::kBulletSpeed, 0);

        if (bullet.getPosition().x < 0 || bullet.getPosition().x > Game::getWindowWidth() ||
            bullet.getPosition().y < 0 || bullet.getPosition().y > Game::getWindowHeight())
        {
            bullet.setState(Bullet::State::Inactive);
        }
    }
}

void BulletManager::handleCollisions(std::vector<Brick>& bricks)
{
    for (auto& bullet : m_bullets)
    {
        for (auto& brick : bricks)
        {
            if (bullet.getSprite().getGlobalBounds().intersects(brick.getSprite().getGlobalBounds()))
            {
                bullet.setState(Bullet::State::Inactive);
                if (brick.hit())
                {
                    std::erase_if(bricks, [&brick](const Brick& other)
                    {
                        return brick == other;
                    });
                }
                break;
            }
        }
    }

    std::erase_if(m_bullets, [](const Bullet& bullet){
        return bullet.getState() == Bullet::State::Inactive;
    });
}

void BulletManager::draw(sf::RenderWindow& window) const
{
    for (auto& bullet : m_bullets)
    {
        window.draw(bullet);
    }
}
