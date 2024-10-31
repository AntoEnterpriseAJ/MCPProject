#include "Player.h"

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f vel)
    : GameObject(pos, texture, vel)
{}

void Player::movePlayer(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_sprite.move(0, -0.5); // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_sprite.move(0, 0.5); // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_sprite.move(-0.5, 0); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_sprite.move(0.5, 0); // Move right
    }
}


