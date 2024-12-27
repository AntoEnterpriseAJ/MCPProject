#pragma once
#include "Obstacle.h"
#include "Vec2f.h"

class BombBrick : public Obstacle
{
public:
    BombBrick(
        const Vec2f& pos,
        int explosionRadius = 3
    );

    ~BombBrick() override = default;

    int getExplosionRadius() const noexcept;

private:
    int m_explosionRadius;
};
