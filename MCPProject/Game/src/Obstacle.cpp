#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f pos, const sf::Texture& texture, bool isPassable, bool isDestroyable, sf::Vector2f size)
	: GameObject(pos, texture, size), m_isPassable(isPassable), m_isDestroyable(isDestroyable)
{
}

bool Obstacle::isPassable()
{
	return m_isPassable;
}

bool Obstacle::isDestroyable()
{
	return m_isDestroyable;
}

float Obstacle::getObstacleSize()
{
	return kObstacleSize;
}
