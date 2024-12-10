#include "Bush.h"

Bush::Bush(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size), m_isPassable(true)
{
}

bool Bush::isPassable() const
{
    return m_isPassable;
}
