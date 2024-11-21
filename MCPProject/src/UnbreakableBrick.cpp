// UnbreakableBrick.cpp
#include "UnbreakableBrick.h"

UnbreakableBrick::UnbreakableBrick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : Brick(pos, texture, false, size)
{
}

bool UnbreakableBrick::isPassable() const
{
    return m_isPassable;
}

void UnbreakableBrick::hit()
{
    // empty
}

bool UnbreakableBrick::isDestroyed() const
{
    return false;
}

sf::FloatRect UnbreakableBrick::getBounds() const
{
    return getSprite().getGlobalBounds();
}
