#include "Player.h"
#include <variant>
#include <vector>
#include <iostream>

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ kPlayerHealth }, m_direction{Direction::Left}
    , m_timeElapsed{ 0 }, m_lives{ kPlayerLives }, m_state{ PlayerState::Alive }
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

Direction Player::GetDirection() const
{
    return m_direction;
}

void Player::Update(float deltaTime)
{
    m_timeElapsed += deltaTime;
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
    m_sprite.setRotation(getRotation(direction));
}

void Player::setLives(uint16_t lives)
{
    m_lives = lives;
}

void Player::setHealth(uint16_t health)
{
    m_health = health;
}

void Player::setState(PlayerState state)
{
    m_state = state;
}

bool Player::isAlive() const
{
    return m_state == PlayerState::Alive;
}

bool Player::canShoot() const
{
    return m_timeElapsed >= kCooldownTime;
}

// client side only movement, maybe will use later
void Player::move(Direction direction, float deltaTime)
{
    auto alignToGrid = [](float value, int gridSize) -> float {
        return std::round(value / gridSize) * gridSize;
    };

    sf::Vector2f newPosition = m_sprite.getPosition();

    if (direction != m_direction)
    {
        if (direction == Direction::Up || direction == Direction::Down)
        {
            newPosition.x = alignToGrid(newPosition.x, 20);
        }
        else if (direction == Direction::Left || direction == Direction::Right)
        {
            newPosition.y = alignToGrid(newPosition.y, 20);
        }
    }

    m_direction = direction;
    if (direction == Direction::Up)
    {
        newPosition.y -= kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Down)
    {
        newPosition.y += kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Left)
    {
        newPosition.x -= kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Right)
    {
        newPosition.x += kPlayerSpeed * deltaTime;
    }

    m_sprite.setPosition(newPosition);
    m_sprite.setRotation(getRotation(m_direction));
}

void Player::resetShootCooldown()
{
    m_timeElapsed = 0;
}

PlayerState Player::GetState() const
{
    return m_state;
}

uint16_t Player::GetLives() const
{
    return m_lives;
}

uint16_t Player::GetHealth() const
{
    return m_health;
}

