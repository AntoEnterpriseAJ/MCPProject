#include "BombBrick.h"

BombBrick::BombBrick(
    const sf::Vector2f& pos,
    const sf::Texture& texture,
    int explosionRadius
)
	: Obstacle(pos, texture, { kObstacleSize, kObstacleSize }, false, true),
	  m_explosionRadius(explosionRadius)
{}

int BombBrick::getExplosionRadius() const noexcept
{
	return m_explosionRadius;
}