// UnbreakableBrick.cpp
#include "UnbreakableBrick.h"

UnbreakableBrick::UnbreakableBrick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : Brick(pos, texture, false, size), m_isPassable(false)
{
}

bool UnbreakableBrick::isPassable() const
{
    return m_isPassable;
}
