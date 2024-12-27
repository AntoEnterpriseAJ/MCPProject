#include "Obstacle.h"

Obstacle::Obstacle(
    const Vec2f& pos,
    const Vec2f& size,
    bool         isPassable,
    bool         isDestroyable
)
	: GameObject(pos, size), m_isPassable(isPassable), m_isDestroyable(isDestroyable)
{}

bool Obstacle::isPassable() const
{
	return m_isPassable;
}

bool Obstacle::isDestroyable() const
{
	return m_isDestroyable;
}
