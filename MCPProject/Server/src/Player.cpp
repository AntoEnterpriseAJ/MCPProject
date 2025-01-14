#include "Player.h"

Player::Player(const Vec2f& position, const Vec2f& size, Direction direction, uint16_t lives, uint16_t health)
    : GameObject(position, size), m_direction{ direction }, m_lives{ lives }
    , m_respawnPosition{}, m_state{ PlayerState::Alive }, m_health{ health }
{
    this->setOrigin(size / 2.0f);
}

Direction Player::GetDirection() const
{
    return m_direction;
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

void Player::resetShootCooldown()
{
    m_lastShoot = std::chrono::steady_clock::now();
}

void Player::hit(int damage)
{
    m_health = std::max(0, m_health - damage);
    if (m_health == 0)
    {
        kill();
    }
}

void Player::kill()
{
    if (m_lives == 0)
    {
        eliminate();
    }
    else
    {
        m_state = PlayerState::Respawning;
        m_lastRespawn = std::chrono::steady_clock::now();
        --m_lives;
    }
}

void Player::eliminate()
{
    m_state = PlayerState::Eliminated;
}

void Player::respawn()
{
    m_state = PlayerState::Alive;
    m_health = kPlayerHealth;
}

bool Player::isEliminated() const
{
    return m_state == PlayerState::Eliminated;
}

bool Player::isAlive() const
{
    return m_state == PlayerState::Alive;
}

bool Player::canShoot() const
{
    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - m_lastShoot).count();
    return deltaTime >= kCooldownTime;
}

bool Player::canRespawn() const
{
    if (m_state == PlayerState::Eliminated)
    {
        return false;
    }

    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - m_lastRespawn).count();
    return deltaTime >= kRespawnTime;
}

void Player::setDirection(Direction direction)
{
    if (m_direction != direction)
    {
        m_direction = direction;

        switch (direction)
        {
        case Direction::Up:
            this->rotate(0);
            break;
        case Direction::Down:
            this->rotate(180);
            break;
        case Direction::Left:
            this->rotate(270);
            break;
        case Direction::Right:
            this->rotate(90);
            break;
        }
    }
}

void Player::setRespawnPosition(const Vec2f& position)
{
    m_respawnPosition = position;
}
