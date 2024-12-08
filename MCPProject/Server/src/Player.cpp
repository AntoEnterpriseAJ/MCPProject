#include "Player.h"

Player::Player(Position position)
    : m_position(position)
{}

Player::Position Player::getPosition() const
{
    return m_position;
}
