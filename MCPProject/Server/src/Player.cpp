#include "Player.h"

Player::Player(const Vec2f& position, const Vec2f& size, Direction direction)
    : GameObject(position, size), m_direction{direction}
{
    this->setOrigin(size / 2.0f);
}

Direction Player::GetDirection() const
{
    return m_direction;
}

void Player::restartCooldown()
{
    m_lastUpdated = std::chrono::steady_clock::now();
}


bool Player::canShoot() const
{
    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - m_lastUpdated).count();
    return deltaTime >= kCooldownTime;
}

void Player::setDirection(Direction direction)
{
    if (m_direction != direction)
    {
        m_direction = direction;

        if (direction == Direction::Up || direction == Direction::Down)
        {
            setSize({getSize().y, getSize().x});
        }
        else
        {
            setSize({39.9f, 39.9f});
        }
    }
}
