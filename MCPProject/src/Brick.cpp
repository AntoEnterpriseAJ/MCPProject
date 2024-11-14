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
        this->destroy();
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

void Brick::destroy()
{
    auto& bricks = Level::getBricks();

    bricks.erase(
        std::remove_if(
            bricks.begin(),
            bricks.end(),
            [this](const std::variant<Brick, Bush>& obj) {
                if (std::holds_alternative<Brick>(obj)) // Adaugă verificarea aici
                {
                    const Brick& brick = std::get<Brick>(obj);
                    return &brick == this;
                }
                return false;
            }),
        bricks.end()
    );
}

sf::FloatRect Brick::getBounds() const
{
    return getSprite().getGlobalBounds();
}

bool Brick::operator==(const Brick& other) const
{
    return this == &other;
}
