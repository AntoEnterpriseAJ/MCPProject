#include "Player.h"
#include "Bullet.h"

Player::Player(const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(400, 300);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Player::movePlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_sprite.move(0, -1);
        dir = Direction::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_sprite.move(0, 1);
        dir = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_sprite.move(-1, 0);
        dir = Direction::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_sprite.move(1, 0);
        dir = Direction::RIGHT;
    }
}

void Player::shoot()
{
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

float Player::getX() const
{
    return m_sprite.getPosition().x;
}

float Player::getY() const
{
    return m_sprite.getPosition().y;
}

float Player::getWidth() const
{
    return m_sprite.getGlobalBounds().width;
}

float Player::getHeight() const
{
    return m_sprite.getGlobalBounds().height;
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}
