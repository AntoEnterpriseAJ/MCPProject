#include "BulletManager.h"
#include "Game.h"
#include "ResourceManager.h"
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

    for (auto& explosion : m_explosions)
    {
        explosion.update(deltaTime);
    }
}

void BulletManager::destroyInArea(const sf::Vector2f& bombPosition, Level& level, float radius)
{
    std::vector<LevelObject>& levelLayout = level.getBricks();

    auto isWithinRadius = [&](const LevelObject& object) -> bool {
        return std::visit([&](auto& obj) -> bool {
            using objType = std::decay_t<decltype(obj)>;

            if constexpr (
                std::is_same_v<objType, Brick> ||
                std::is_same_v<objType, BombBrick> || 
                std::is_same_v<objType, Bush>)
            {
                float distance = std::sqrt(std::pow(obj.getPosition().x - bombPosition.x, 2) +
                    std::pow(obj.getPosition().y - bombPosition.y, 2));
                return distance <= radius;
            }
            return false;
            }, object);
        };

    levelLayout.erase(std::remove_if(levelLayout.begin(), levelLayout.end(), isWithinRadius), levelLayout.end());
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

                if constexpr (std::is_same_v<objType, Brick> || std::is_same_v<objType, UnbreakableBrick>)
                {
                    if (bullet.getBounds().intersects(obj.getBounds()))
                    {
                        bullet.setState(Bullet::State::Inactive);
                        addExplosion(bullet);
                        obj.hit();
                    }
                }
                else if constexpr (std::is_same_v<objType, BombBrick>)
                {
                    if (bullet.getBounds().intersects(obj.getBounds()))
                    {
                        bullet.setState(Bullet::State::Inactive);
                        addExplosion(bullet);
                        obj.hit();

                        this->destroyInArea(obj.getPosition(), level, obj.GetExplosionRadius() * Brick::getSize());
                    }
                }
                }, object);
        }
    }

    removeInactive(level);
}


void BulletManager::addExplosion(const Bullet& bullet)
{
    Direction direction = bullet.getDirection();

    switch (direction)
    {
    case Direction::Right:
        m_explosions.push_back(
            Explosion(bullet.getPosition() + sf::Vector2f(bullet.getSize().x / 2.0f, 0),
                ResourceManager::getInstance().getTexture("explosionSheet"))
        );
        break;
    case Direction::Left:
        m_explosions.push_back(
            Explosion(bullet.getPosition() - sf::Vector2f(bullet.getSize().x / 2.0f, 0),
                ResourceManager::getInstance().getTexture("explosionSheet"))
        );
        break;
    case Direction::Up:
        m_explosions.push_back(
            Explosion(bullet.getPosition() - sf::Vector2f(0, bullet.getSize().y / 2.0f),
                ResourceManager::getInstance().getTexture("explosionSheet"))
        );
        break;
    case Direction::Down:
        m_explosions.push_back(
            Explosion(bullet.getPosition() + sf::Vector2f(0, bullet.getSize().y / 2.0f),
                ResourceManager::getInstance().getTexture("explosionSheet"))
        );
    }
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

    std::erase_if(m_explosions, [](const Explosion& explosion) {
        return explosion.hasFinished();
    });
}

void BulletManager::draw(sf::RenderWindow& window) const
{
    for (auto& bullet : m_bullets)
    {
        window.draw(bullet);
    }

    for (auto& explosion : m_explosions)
    {
        window.draw(explosion);
    }
}
