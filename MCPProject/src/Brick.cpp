#include "Brick.h"
#include "Level.h"

Brick::Brick(sf::Vector2f pos, const sf::Texture& texture, bool isDestroyable, sf::Vector2f size)
    : GameObject(pos, texture, size), m_isDestroyable(isDestroyable)
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

bool Brick::isInArea(const sf::Vector2f& upLeft, const sf::Vector2f& downRight)
{
    // TODO: Find a way to convert from getPosition().x type to int 
    //       to be able to use list initialization
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    return x >= upLeft.x && x <= downRight.x &&
        y <= upLeft.y && y >= downRight.y;
}

sf::FloatRect Brick::getBounds() const
{
    return getSprite().getGlobalBounds();
}

bool Brick::operator==(const Brick& other) const
{
    return this == &other;
}
