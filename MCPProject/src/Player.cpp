#include "Player.h"
#include "Bullet.h"

Player::Player(sf::RectangleShape rect)
    : m_rectangle(rect)
{
    m_rectangle.setFillColor(sf::Color::Blue); // Player color
    m_rectangle.setPosition(400, 300); // Initial pozition
}

void Player::movePlayer(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_rectangle.move(0, -1); // Move up
        dir = Direction::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_rectangle.move(0, 1); // Move down
        dir = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_rectangle.move(-1, 0); // Move left
        dir = Direction::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_rectangle.move(1, 0); // Move right
        dir = Direction::RIGHT;
    }
}

void Player::shoot() {
    float centerX = getX() + getWidth() / 2.0f;
    float centerY = getY() + getHeight() / 2.0f;

    Bullet newBullet(static_cast<int>(centerX), static_cast<int>(centerY), dir, 5);
    bullets.push_back(newBullet);
}


void Player::updateBullets()
{
    for (auto& bullet : bullets)
    {
        bullet.update();
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
        return !bullet.getIsActive();
        }), bullets.end());
}

sf::RectangleShape Player::getPlayerShape()
{
    return m_rectangle;
}

float Player::getX() const
{
    return m_rectangle.getPosition().x;
}

float Player::getY() const
{
    return m_rectangle.getPosition().y;
}

float Player::getWidth() const
{
    return m_rectangle.getSize().x;
}

float Player::getHeight() const
{
    return m_rectangle.getSize().y;
}

void Player::setColor(const sf::Color& color)
{
    m_color = color;
    m_rectangle.setFillColor(m_color);
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}
