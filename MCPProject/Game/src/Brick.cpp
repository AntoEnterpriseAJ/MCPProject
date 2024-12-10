#include "Brick.h"

Brick::Brick(sf::Vector2f pos, const sf::Texture& texture)
    : Obstacle(pos, texture, false, true), m_brickHealth(3)
{
}

bool Brick::isDestroyed() const
{
    return m_brickHealth <= 0;
}

void Brick::hit()
{
    m_brickHealth--;
}
