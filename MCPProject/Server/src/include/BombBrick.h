#pragma once
#include "Obstacle.h"
#include "Vec2f.h"

class BombBrick : public Obstacle
{
public:
    BombBrick(
        const Vec2f& pos,
        float explosionRadius = kExplosionRadius
    );

    ~BombBrick() override = default;

    int getExplosionRadius() const noexcept;
public:
    static constexpr float kExplosionRadius{ 2.0f };
private:
    float m_explosionRadius;
};
