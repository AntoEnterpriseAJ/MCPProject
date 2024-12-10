#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"
#include "Explosion.h"
#include <variant>

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(Level& level, float deltaTime);

    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(Level& level);
    void addExplosion(const Bullet& bullet);
    void removeInactive(Level& level);
    void destroyInArea(const sf::Vector2f& bombPosition, Level& level, float radius);

private:
    std::vector<Bullet>    m_bullets;
    std::vector<Explosion> m_explosions; 
};
