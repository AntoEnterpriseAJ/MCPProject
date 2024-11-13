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

bool Brick::hit()
{
    m_brickHealth--;
    if (m_brickHealth <= 0)
    {
        this->destroyArea();
    }

    return m_brickHealth <= 0;
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

void Brick::destroyArea()
{
    sf::Vector2f brickPos{ this->getPosition() };

    sf::Vector2f upLeft{ sf::Vector2f(
        brickPos.x - kBrickSize * m_explosionRadius,
        brickPos.y + kBrickSize * m_explosionRadius
    ) };

    sf::Vector2f downRight{ sf::Vector2f(
        brickPos.x + kBrickSize * m_explosionRadius,
        brickPos.y - kBrickSize * m_explosionRadius
    ) };
    
    for (Brick& brick : Level::getBricks())
    {
        if (brick.isInArea(upLeft, downRight))
        {
            Level::getBricks().erase(
                std::remove(
                    Level::getBricks().begin(), 
                    Level::getBricks().end(), brick
                ), Level::getBricks().end()
            );
        }
    }
}

sf::FloatRect Brick::getBounds() const
{
    return getSprite().getGlobalBounds();
}

bool Brick::operator==(const Brick& other) const
{
    return this == &other;
}
