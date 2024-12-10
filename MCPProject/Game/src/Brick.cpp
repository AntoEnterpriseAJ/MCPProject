#include "Brick.h"
#include "Level.h"

Brick::Brick(sf::Vector2f pos, const sf::Texture& texture, bool isDestroyable, sf::Vector2f size)
    : GameObject(pos, texture, size), m_isDestroyable(isDestroyable), m_brickHealth(3)
{
}

int Brick::getSize() 
{
    return kBrickSize;
}

bool Brick::isDestroyed() const
{
    return m_brickHealth <= 0;
}

void Brick::hit()
{
    m_brickHealth--;
}
