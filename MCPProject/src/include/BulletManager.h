#pragma once
#include "Bullet.h"
#include "Brick.h"
#include "Player.h"
#include <variant>

class BulletManager
{
public:
    void addBullet(const Bullet& bullet);
    void update(std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& level, float deltaTime);

    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& level);
    void removeInactive(std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& level);
private:
    std::vector<Bullet> m_bullets;
};
