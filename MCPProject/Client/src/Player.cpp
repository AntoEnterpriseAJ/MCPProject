#include "Player.h"
#include <variant>
#include <vector>
#include <iostream>

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_direction{Direction::Left}
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

Direction Player::getDirection() const
{
    return m_direction;
}