#pragma once

#include "GameObject.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include "Explosion.h"
#include <vector>
#include <memory>

class BulletManager {
public:
    void draw(sf::RenderWindow& window) const;
    void addExplosion(const Bullet& bullet);

    void clearBullets() noexcept;
    void addBullet(std::unique_ptr<Bullet> bullet);

private:
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Explosion>> m_explosions;
};
