#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "PlayerState.h"
#include "PowerUp.h"

class Player : public GameObject
{
public:
    Player() = default;
    Player(
        const Vec2f& position,
        const Vec2f& size = { kPlayerSizeX, kPlayerSizeY },
        Direction direcion = Direction::Left,
        uint16_t lives = kPlayerLives,
        uint16_t health = kPlayerHealth
    );
    ~Player() override = default;

    void setPoints(uint16_t points);
    void setDirection(Direction direction);
    void setDatabaseID(uint16_t databaseID);
    void setDamageMultiplier(float multiplier);
    void setRespawnPosition(const Vec2f& position);
    void resetShootCooldown();

    void hit(int damage);
    void kill();
    void eliminate();
    void respawn();
    void addPoints(uint16_t points);
    void addPowerUp(std::unique_ptr<PowerUp> powerUp);
    void updatePowerUps();
    void setBoughtSpecialPowerUp(bool bought);

    bool getBoughtSpecialPowerUp() const;
    bool isAlive() const;
    bool isEliminated() const;
    bool canShoot() const;
    bool canRespawn() const;
    Direction   GetDirection() const;
    PlayerState GetState() const;
    uint16_t    getDatabaseID() const;
    uint16_t    GetLives() const;
    uint16_t    GetHealth() const;
    uint16_t    GetPoints() const;
    float       getSpeed() const;
    float       getBulletDamageMultiplier() const;
    float       getBulletSpeedMultiplier() const;
public:
    static constexpr float    kCooldownTime = 0.5f;
    static constexpr float    kPlayerSpeed = 150.0f;
    static constexpr float    kRespawnTime = 3.0f;
    static constexpr float    kPlayerSizeX  = 39.9f;
    static constexpr float    kPlayerSizeY  = 39.9f;
    static constexpr uint16_t kPlayerHealth = 100.0f;
    static constexpr uint16_t kPlayerLives  = 3;
private:
    void applyPowerUp(const std::unique_ptr<PowerUp>& powerUp);
    void deactivatePowerUp(std::unique_ptr<PowerUp>& powerUp);
private:
    uint16_t    m_lives;
    uint16_t    m_health;
    uint16_t    m_points;
    uint16_t    m_databaseID;
    Direction   m_direction : 2;
    Vec2f       m_respawnPosition;
    PlayerState m_state : 2;
    float       m_playerSpeed;
    float       m_bulletDamageMultiplier;
    float       m_bulletSpeedMultiplier;
    float       m_shootCooldown;
    bool        m_boughtSpecialPowerUp;

    std::vector<std::unique_ptr<PowerUp>> m_powerUps;

    std::chrono::steady_clock::time_point m_lastShoot;
    std::chrono::steady_clock::time_point m_lastRespawn;
};