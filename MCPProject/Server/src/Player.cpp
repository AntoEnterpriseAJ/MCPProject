#include "Player.h"

Player::Player(const Position& position, uint16_t id)
    : m_position(position)
{}

Player::Position Player::getPosition() const
{
    return m_position;
}

Direction Player::getDirection() const
{
    return m_direction;
}

void Player::move(Direction direction, float deltaTime)
{
    auto alignToGrid = [](float value, int gridSize) -> float {
        return std::round(value / gridSize) * gridSize;
    };

    Position newPosition = m_position;

    if (direction != m_direction)
    {
        if (direction == Direction::Up || direction == Direction::Down)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }
        else if (direction == Direction::Left || direction == Direction::Right)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }
    }

    m_direction = direction;

    float xOffset{ 0 }, yOffset{ 0 };
    if (direction == Direction::Up)
    {
        yOffset -= kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Down)
    {
        yOffset += kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Left)
    {
        xOffset -= kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Right)
    {
        xOffset += kPlayerSpeed * deltaTime;
    }

    m_position.x += xOffset;
    m_position.y += yOffset;
}
