#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Level.h"
#include <vector>
#include <memory>

class BulletManager {
public:
    void addBullet(std::unique_ptr<Bullet> bullet);
    void update(Level& level, float deltaTime);
    void draw(sf::RenderWindow& window) const;

private:
    void handleCollisions(Level& level);
    void addExplosion(const Bullet& bullet);
    void removeInactive(Level& level);

    void detonate(const sf::Vector2f& bombPosition, Level& level, int radius);

private:
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Explosion>> m_explosions;
};
