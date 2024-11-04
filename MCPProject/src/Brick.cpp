#include "Brick.h"

Brick::Brick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size)
{

}

bool Brick::hit() 
{
    health--;
    return health <= 0;
}

int Brick::getSize() 
{
    return m_brickSize;
}

sf::FloatRect Brick::getBounds() const
{
    return getSprite().getGlobalBounds();
}

bool Brick::operator==(const Brick& other) const
{
    return this == &other;
}
