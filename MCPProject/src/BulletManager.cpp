#include "BulletManager.h"
#include "Game.h"


#include <iostream>

void BulletManager::addBullet(const Bullet& bullet)
{
    m_bullets.push_back(bullet);
    std::cout << m_bullets.size() << "\n";
    std::cout << bullet.getSize().x << " " << bullet.getSize().y << "\n";
}

void BulletManager::update(std::vector<std::variant<Brick, Bush>>& level)
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

//TODO: check if this is actually this painful to write
void BulletManager::handleCollisions(std::vector<std::variant<Brick, Bush>>& level)
{
    for (auto& bullet : m_bullets)
    {
        // TODO: don't check for every obj, check only the surroundings of the bullet
        for (auto& object : level)
        {
            std::visit([&](auto& obj) {
                using objType = std::decay_t<decltype(obj)>;

                if constexpr (std::is_same_v<objType, Brick>)
                {
                    if (bullet.getSprite().getGlobalBounds().intersects(obj.getSprite().getGlobalBounds()))
                    {
                        bullet.setState(Bullet::State::Inactive);
                        obj.hit();
                    }
                }
            }, object);
        }
    }

    removeInactive(level);
}

//TODO: check if this is actually this painful to write
void BulletManager::removeInactive(std::vector<std::variant<Brick, Bush>>& level)
{
    std::erase_if(level, [](const std::variant<Brick, Bush>& object){
        return std::visit([](const auto& obj) -> bool {
            using objType = std::decay_t<decltype(obj)>;
            if constexpr (std::is_same_v<objType, Brick>)
            {
                return obj.isDestroyed();
            }
            else
            {
                return false;
            }
        }, object);
    });

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
