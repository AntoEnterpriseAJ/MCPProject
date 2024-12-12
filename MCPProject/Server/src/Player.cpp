#include "Player.h"

Player::Player(const Position& position, uint16_t id)
    : m_position(position), m_id{id}
{}

Player::Position Player::getPosition() const
{
    return m_position;
}

uint16_t Player::getID() const
{
    return m_id;
}
