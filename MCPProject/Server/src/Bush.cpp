#include "Bush.h"

Bush::Bush(const Vec2f& pos)
    : Obstacle{pos, { kObstacleSize, kObstacleSize }, true, false}
{
}

bool Bush::isPassable() const
{
    return m_isPassable;
}
