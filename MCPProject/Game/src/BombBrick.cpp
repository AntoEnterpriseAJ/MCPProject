#include "BombBrick.h"
#include <variant>

BombBrick::BombBrick(sf::Vector2f pos, const sf::Texture& texture, bool isDestroyable, sf::Vector2f size)
	: Brick(pos, texture, isDestroyable, size)
{
}

int BombBrick::GetExplosionRadius()
{
	return m_explosionRadius;
}
