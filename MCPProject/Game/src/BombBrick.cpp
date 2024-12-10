#include "BombBrick.h"
#include <variant>

BombBrick::BombBrick(sf::Vector2f pos, const sf::Texture& texture)
	: Obstacle(pos, texture, false, true), m_explosionRadius(3)
{
}

int BombBrick::GetExplosionRadius()
{
	return m_explosionRadius;
}
