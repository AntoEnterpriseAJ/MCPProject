#include "Bush.h"

Bush::Bush(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size)
{
}

bool Bush::isPassable() const
{
    return m_isPassable;
}

sf::FloatRect Bush::getBounds() const
{
    return getSprite().getGlobalBounds();
}

bool Bush::operator==(const Bush& other) const
{
    return this == &other;
}
