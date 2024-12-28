#include "Player.h"

Player::Player(const Vec2f& position, const Vec2f& size, Direction direction)
    : GameObject(position, size), m_direction{direction}
{
    this->setOrigin(size / 2.0f);
}

Direction Player::GetDirection() const
{
    return m_direction;
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
}
