#include "Player.h"
#include "Game.h"
#include "Brick.h"
#include <iostream>
#include <cmath>
#include <memory>

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size), m_health(100), m_cooldownDuration(0), m_direction(Direction::Left)
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

void Player::update(float deltaTime)
{
    if (m_cooldownDuration > 0)
    {
        m_cooldownDuration -= deltaTime;
        if (m_cooldownDuration < 0) m_cooldownDuration = 0;
    }
}

bool Player::canShoot() const
{
    return m_cooldownDuration <= 0;
}

void Player::restartCooldown()
{
    m_cooldownDuration = kCooldownTime;
}

bool Player::canMove(const Level& level, float deltaTime)
{
    sf::FloatRect playerBounds = getBounds();
    sf::Vector2f movement;

    switch (m_direction)
    {
        case Direction::Up: movement.y = -kPlayerSpeed * deltaTime; break;
        case Direction::Down: movement.y = kPlayerSpeed * deltaTime; break;
        case Direction::Left: movement.x = -kPlayerSpeed * deltaTime; break;
        case Direction::Right: movement.x = kPlayerSpeed * deltaTime; break;
    }

    playerBounds.left += movement.x;
    playerBounds.top += movement.y;

    const auto& levelLayout = level.getBricks();
    for (const auto& obj : levelLayout)
    {
        if (obj && !obj->isPassable() && playerBounds.intersects(obj->getBounds()))
        {
            return false;
        }
    }

    return true;
}

void Player::movePlayer(const Level& level, float deltaTime)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    auto alignToGrid = [](float value, int gridSize) -> float {
        return std::round(value / gridSize) * gridSize;
        };

    sf::Vector2f newPosition = m_sprite.getPosition();
    float rotation = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (m_direction != Direction::Up)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }

        m_direction = Direction::Up;
        rotation = 0;

        if (canMove(level, deltaTime) && playerBounds.top > 0)
        {
            newPosition.y -= kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (m_direction != Direction::Down)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }

        m_direction = Direction::Down;
        rotation = 180;

        if (canMove(level, deltaTime) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            newPosition.y += kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (m_direction != Direction::Left)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }

        m_direction = Direction::Left;
        rotation = 270;

        if (canMove(level, deltaTime) && playerBounds.left > 0)
        {
            newPosition.x -= kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (m_direction != Direction::Right)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }

        m_direction = Direction::Right;
        rotation = 90;

        if (canMove(level, deltaTime) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            newPosition.x += kPlayerSpeed * deltaTime;
        }
    }

    m_sprite.setPosition(newPosition);
    m_sprite.setRotation(rotation);
}

Direction Player::getDirection() const
{
    return m_direction;
}
