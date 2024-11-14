#include "Player.h"
#include "Bullet.h"
#include "Brick.h"
#include "Game.h"
#include "Bush.h"
#include <variant>
#include <vector>

#include <algorithm>

#include <iostream> // Only used for the cerr below, TODO: delete it

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_dir{Direction::LEFT} //Health currently unused
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_cooldownDuration = 0.5f;
}

bool Player::canMove(Direction direction, const std::vector<std::variant<Brick, Bush>>& levelLayout)
Direction Player::getDirection() const
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    sf::Vector2f movement = { 0, 0 };
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
        movement.y = -kPlayerSpeed;
        break;
    case Direction::DOWN:
        movement.y = kPlayerSpeed;
        break;
    case Direction::LEFT:
        movement.x = -kPlayerSpeed;
        break;
    case Direction::RIGHT:
        movement.x = kPlayerSpeed;
        break;
    }

    playerBounds.left += movement.x;
    playerBounds.top += movement.y;

    for (const auto& obj : levelLayout)
    {
        if (auto* brick = std::get_if<Brick>(&obj))
        {
            if (playerBounds.intersects(brick->getBounds()))
            {
                return false;
            }
        }
        else if (auto* bush = std::get_if<Bush>(&obj))
        {
            if (playerBounds.intersects(bush->getBounds()))
            {
                //return false;
            }
        }
    }
    return true;
}


void Player::movePlayer(const std::vector<std::variant<Brick, Bush>>& levelLayout)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_dir = Direction::UP;
        m_sprite.setRotation(0.0f);

        if (canMove(Direction::UP, levelLayout) && playerBounds.top > 0)
        {
            m_sprite.move(0, -kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);

        if (canMove(Direction::DOWN, levelLayout) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            m_sprite.move(0, kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);

        if (canMove(Direction::LEFT, levelLayout) && playerBounds.left > 0)
        {
            m_sprite.move(-kPlayerSpeed, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);

        if (canMove(Direction::RIGHT, levelLayout) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            m_sprite.move(kPlayerSpeed, 0);
        }
    }
}

void Player::restartTimer()
{
    m_cooldownClock.restart();
}
