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

void Player::Update(float deltaTime)
{
    if (m_cooldownDuration > 0)
    {
        m_cooldownDuration -= deltaTime;
        if (m_cooldownDuration < 0) m_cooldownDuration = 0;
    }
}

bool Player::CanShoot() const
{
    return m_cooldownDuration <= 0;
}

void Player::RestartCooldown()
{
    m_cooldownDuration = kCooldownTime;
}

bool Player::CanMove(const Level& level, float deltaTime)
{
    sf::FloatRect playerBounds = GetBounds();
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
        if (obj && !obj->isPassable() && playerBounds.intersects(obj->GetBounds()))
        {
            return false;
        }
    }

    return true;
}

void Player::MovePlayer(const Level& level, float deltaTime)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    auto alignToGrid = [](float value, int gridSize) -> float {
        return std::round(value / gridSize) * gridSize;
        };

    sf::Vector2f newPosition = m_sprite.getPosition();
    bool keyPressed = false;
    float rotation = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        keyPressed = true;
        if (m_direction != Direction::Up)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }

        m_direction = Direction::Up;
        rotation = 0;

        if (CanMove(level, deltaTime) && playerBounds.top > 0)
        {
            newPosition.y -= kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        keyPressed = true;
        if (m_direction != Direction::Down)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }

        m_direction = Direction::Down;
        rotation = 180;

        if (CanMove(level, deltaTime) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            newPosition.y += kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        keyPressed = true;
        if (m_direction != Direction::Left)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }

        m_direction = Direction::Left;
        rotation = 270;

        if (CanMove(level, deltaTime) && playerBounds.left > 0)
        {
            newPosition.x -= kPlayerSpeed * deltaTime;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        keyPressed = true;
        if (m_direction != Direction::Right)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }

        m_direction = Direction::Right;
        rotation = 90;

        if (CanMove(level, deltaTime) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            newPosition.x += kPlayerSpeed * deltaTime;
        }
    }

    m_sprite.setPosition(newPosition);
    if (keyPressed)
    {
        m_sprite.setRotation(rotation);
    }
}

Direction Player::GetDirection() const
{
    return m_direction;
}
