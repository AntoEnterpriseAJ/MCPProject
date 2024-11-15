#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(std::vector<std::variant<Brick, Bush>>& level, float deltaTime);

    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(std::vector<std::variant<Brick, Bush>>& level);
    void removeInactive(std::vector<std::variant<Brick, Bush>>& level);
private:
    std::vector<Bullet> m_bullets;
};
