#include "BombBrick.h"

BombBrick::BombBrick(
    const Vec2f& pos,
    float explosionRadius
)
	: Obstacle(pos, { kObstacleSize, kObstacleSize }, false, true),
	  m_explosionRadius(explosionRadius)
{}

int BombBrick::getExplosionRadius() const noexcept
{
	return m_explosionRadius;
}