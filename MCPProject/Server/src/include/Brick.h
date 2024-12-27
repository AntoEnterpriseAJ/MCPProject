#pragma once
#include "Obstacle.h"
#include "Vec2f.h"

class Brick : public Obstacle
{
public:
    Brick(
        const Vec2f& pos,
        int          health = 3,
        bool         passable = false,
        bool         destroyable = true
    );

    ~Brick() override = default;

    bool isDestroyed() const noexcept;
    void hit();

private:
    int m_brickHealth;
};