#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(std::vector<std::variant<Brick, Bush>>& level);

    void draw(sf::RenderWindow& window) const;

private:
    // TODO: Repair the collision cause the merge broke it
    void handleCollisions(std::vector<std::variant<Brick, Bush>>& level);
private:
    std::vector<Bullet> m_bullets;
};
