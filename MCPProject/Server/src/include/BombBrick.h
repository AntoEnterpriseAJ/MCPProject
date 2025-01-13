#pragma once
#include "Obstacle.h"
#include "Vec2f.h"

class BombBrick : public Obstacle
{
public:
    BombBrick(
        const Vec2f& pos,
        float explosionRadius = 3.0
    );

    ~BombBrick() override = default;

    int getExplosionRadius() const noexcept;

private:
    float m_explosionRadius;
};
