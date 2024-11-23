#include "BulletManager.h"
#include "Game.h"
#include "BrickManager.h"
#include <iostream>

void BulletManager::addBullet(const Bullet& bullet)
{
    m_bullets.push_back(bullet);
    std::cout << m_bullets.size() << "\n";
    std::cout << bullet.getSize().x << " " << bullet.getSize().y << "\n";
}

void BulletManager::update(Level& level, float deltaTime)
{
    handleCollisions(level);

    for (auto& bullet : m_bullets)
    {
        bullet.update(deltaTime);

        if (bullet.getPosition().x < 0 || bullet.getPosition().x > Game::getWindowWidth() ||
            bullet.getPosition().y < 0 || bullet.getPosition().y > Game::getWindowHeight())
        {
            bullet.setState(Bullet::State::Inactive);
        }
    }
}

//TODO: check if this is actually this painful to write
void BulletManager::handleCollisions(Level& level)
{
    std::vector<LevelObject>& levelLayout = level.getBricks();

    for (auto& bullet : m_bullets)
    {
        for (auto& object : levelLayout)
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
                else if constexpr (std::is_same_v<objType, UnbreakableBrick>)
                {
                    if (bullet.getSprite().getGlobalBounds().intersects(obj.getSprite().getGlobalBounds()))
                    {
                        bullet.setState(Bullet::State::Inactive);
                    }
                }
                }, object);
        }
    }

    removeInactive(level);
}

//TODO: check if this is actually this painful to write
void BulletManager::removeInactive(Level& level)
{
    std::vector<LevelObject>& levelLayout = level.getBricks();

    std::erase_if(levelLayout, [](const LevelObject& object){
        return std::visit([](const auto& obj) -> bool {
            using objType = std::decay_t<decltype(obj)>;
            if constexpr (std::is_same_v<objType, Brick>)
            {
                if (obj.isDestroyed())
                {
                    //BrickManager::destroyBlocksInArea(level, 3000, obj.getPosition());
                    return true;
                }
              
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
