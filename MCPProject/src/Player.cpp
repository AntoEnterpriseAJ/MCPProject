#include "Player.h"

Player::Player(sf::RectangleShape rect)
{
    m_rectangle = rect;
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(400, 300);
}

void Player::movePlayer(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_rectangle.move(0, -0.1); // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_rectangle.move(0, 0.1); // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_rectangle.move(-0.1, 0); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_rectangle.move(0.1, 0); // Move right
    }
}

sf::RectangleShape Player::getPlayerShape()
{
    return m_rectangle;
}
