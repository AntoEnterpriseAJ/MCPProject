#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(std::vector<Brick>& level);

    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(std::vector<Brick>& bricks);
private:
    std::vector<Bullet> m_bullets;
};
