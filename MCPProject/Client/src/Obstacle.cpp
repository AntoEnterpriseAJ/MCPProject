#include "Obstacle.h"

Obstacle::Obstacle(
    const sf::Vector2f& pos,
    const sf::Texture& texture,
    const sf::Vector2f& size,
    bool isPassable,
    bool isDestroyable
)
	: GameObject(pos, texture, size), m_isPassable(isPassable), m_isDestroyable(isDestroyable)
{}

bool Obstacle::isPassable() const
{
	return m_isPassable;
}

bool Obstacle::isDestroyable() const
{
	return m_isDestroyable;
}
