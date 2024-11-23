#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"
#include <variant>

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(Level& level, float deltaTime);

    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(Level& level);
    void removeInactive(Level& level);
private:
    std::vector<Bullet> m_bullets;
};
