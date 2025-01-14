#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Level.h"
#include <vector>
#include <memory>

class BulletManager {
public:
    void addBullet(std::unique_ptr<Bullet> bullet);
    void update(Level& level, std::unordered_map<uint8_t, Player>& players, float deltaTime);

    const std::vector<std::unique_ptr<Bullet>>& getBullets() const noexcept;
private:
    void handleCollisions(Level& level, std::unordered_map<uint8_t, Player>& players);
    void handlePlayerCollision(std::unordered_map<uint8_t, Player>& players);
    void addExplosion(const Bullet& bullet);
    void removeInactive(Level& level);

    void detonate(const Vec2f& bombPosition, Level& level, float radius);
private:
    std::vector<std::unique_ptr<Bullet>> m_bullets;
};
