#include "Player.h"
#include "Bullet.h"
#include "Brick.h"
#include "Game.h"

#include <algorithm>

#include <iostream> // Only used for the cerr below, TODO: delete it

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_dir{Direction::LEFT} //Health currently unused
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_cooldownDuration = 0.5f;
}

Direction Player::getDirection() const
{
    return m_dir;
}

bool Player::canShoot() const
{
    if (m_cooldownClock.getElapsedTime().asSeconds() >= m_cooldownDuration)
    {
        return true;
    }

    return false;
}

bool Player::canMove(Direction direction, const std::vector<Brick>& bricks) const
{
    sf::FloatRect nextPosition = m_sprite.getGlobalBounds();

    switch (direction)
    {
    case Direction::UP:
        nextPosition.top -= kPlayerSpeed;
        break;
    case Direction::DOWN:
        nextPosition.top += kPlayerSpeed;
        break;
    case Direction::LEFT:
        nextPosition.left -= kPlayerSpeed;
        break;
    case Direction::RIGHT:
        nextPosition.left += kPlayerSpeed;
        break;
    }

    for (const auto& brick : bricks)
    {
        if (nextPosition.intersects(brick.getBounds()))
        {
            return false;
        }
    }
    return true;
}


void Player::movePlayer(const std::vector<Brick>& bricks)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_dir = Direction::UP;
        m_sprite.setRotation(0.0f);

        if (canMove(Direction::UP, bricks) && playerBounds.top > 0)
        {
            m_sprite.move(0, -kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);

        if (canMove(Direction::DOWN, bricks) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            m_sprite.move(0, kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);

        if (canMove(Direction::LEFT, bricks) && playerBounds.left > 0)
        {
            m_sprite.move(-kPlayerSpeed, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);

        if (canMove(Direction::RIGHT, bricks) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            m_sprite.move(kPlayerSpeed, 0);
        }
    }
}

void Player::restartTimer()
{
    m_cooldownClock.restart();
}
