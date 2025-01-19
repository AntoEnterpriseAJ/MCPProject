#include "Player.h"

Player::Player(const Vec2f& position, const Vec2f& size, Direction direction, uint16_t lives, uint16_t health)
    : GameObject(position, size), m_direction{ direction }, m_lives{ lives }, m_respawnPosition{}
    , m_state{ PlayerState::Alive }, m_health{ health }, m_points{ 0 }, m_lastShoot{}, m_lastRespawn{}
    , m_powerUps{}, m_playerSpeed{ kPlayerSpeed }, m_damageMultiplier{ 1.0f }, m_shootCooldown{ kCooldownTime }
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

uint16_t Player::getDatabaseID() const
{
    return m_databaseID;
}

uint16_t Player::GetLives() const
{
    return m_lives;
}

uint16_t Player::GetHealth() const
{
    return m_health;
}

uint16_t Player::GetPoints() const
{
    return m_points;
}

float Player::getSpeed() const
{
    return m_playerSpeed;
}

float Player::getDamageMultiplier() const
{
    return m_damageMultiplier;
}

void Player::applyPowerUp(const std::unique_ptr<PowerUp>& powerUp)
{
    powerUp->Activate();

    switch (powerUp->GetEffect())
    {
    case PowerUpEffect::HealthUp:
        m_health = kPlayerHealth;
        break;
    case PowerUpEffect::SpeedUp:
        m_playerSpeed += kPlayerSpeed * 0.5f;
        break;
    case PowerUpEffect::DamageUp:
        m_damageMultiplier += 0.5f;
        break;
    case PowerUpEffect::ReduceShootCooldown:
        m_shootCooldown -= kCooldownTime * 0.5f;
        break;
    case PowerUpEffect::BulletSpeedUp:
        break;
    }
}

void Player::deactivatePowerUp(std::unique_ptr<PowerUp>& powerUp)
{
    switch (powerUp->GetEffect())
    {
    case PowerUpEffect::HealthUp:
        break;
    case PowerUpEffect::SpeedUp:
        m_playerSpeed -= kPlayerSpeed * 0.5f;
        break;
    case PowerUpEffect::DamageUp:
        m_damageMultiplier -= 0.5f;
        break;
    case PowerUpEffect::ReduceShootCooldown:
        m_shootCooldown += kCooldownTime * 0.5f;
        break;
    case PowerUpEffect::BulletSpeedUp:
        break;
    }
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

void Player::addPoints(uint16_t points)
{
    m_points += points;
}

void Player::addPowerUp(std::unique_ptr<PowerUp> powerUp)
{
    applyPowerUp(powerUp);
    m_powerUps.push_back(std::move(powerUp));
}

void Player::updatePowerUps()
{
    for (auto& powerUp : m_powerUps)
    {
        if (powerUp->HasExpired())
        {
            deactivatePowerUp(powerUp);
        }
    }

    std::erase_if(m_powerUps, [](const auto& powerUp) { return powerUp->HasExpired(); });
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
    return deltaTime >= m_shootCooldown;
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

void Player::setPoints(uint16_t points)
{
    m_points = points;
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

void Player::setDatabaseID(uint16_t databaseID)
{
    m_databaseID = databaseID;
}

void Player::setDamageMultiplier(float multiplier)
{
    m_damageMultiplier = multiplier;
}

void Player::setRespawnPosition(const Vec2f& position)
{
    m_respawnPosition = position;
}
