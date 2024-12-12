#include "Player.h"

Player::Player(const Position& position, uint16_t id)
    : m_position(position)
{}

void Player::setPosition(const Position& position)
{
    m_position = position;
}

Player::Position Player::getPosition() const
{
    return m_position;
}
