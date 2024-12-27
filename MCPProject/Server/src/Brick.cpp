#include "Brick.h"

Brick::Brick(
    const Vec2f& pos,
    int          health,
    bool         passable,
    bool         destroyable
)
    : Obstacle(pos, { kObstacleSize, kObstacleSize }, passable, destroyable)
    , m_brickHealth(health)
{}

bool Brick::isDestroyed() const noexcept
{
    return m_brickHealth <= 0;
}

void Brick::hit()
{
    if (m_brickHealth > 0)
        --m_brickHealth;
}