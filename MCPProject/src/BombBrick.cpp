#include "BombBrick.h"

BombBrick::BombBrick(sf::Vector2f pos, const sf::Texture& texture, bool isDestroyable, sf::Vector2f size)
	: Brick(pos, texture, isDestroyable, size)
{
}

void BombBrick::destroyInArea(const sf::Vector2f& centerExplosionArea)
{
	// TODO: Implement explosions in area
}