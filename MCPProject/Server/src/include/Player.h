#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "PlayerState.h"

class Player : public GameObject
{
public:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;
    static constexpr float kRespawnTime = 3.0f;
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

    void setDirection(Direction direction);
    void setRespawnPosition(const Vec2f& position);
    void resetShootCooldown();

    void hit(int damage);
    void kill();
    void eliminate();
    void respawn();

    bool isAlive() const;
    bool isEliminated() const;
    bool canShoot() const;
    bool canRespawn() const;
    Direction GetDirection() const;
    PlayerState GetState() const;
    uint16_t GetLives() const;
    uint16_t GetHealth() const;
public:
    static constexpr float    kPlayerSizeX  = 39.9f;
    static constexpr float    kPlayerSizeY  = 39.9f;
    static constexpr uint16_t kPlayerHealth = 100.0f;
    static constexpr uint16_t kPlayerLives  = 3;
private:
    uint16_t    m_lives;
    uint16_t    m_health;
    Direction   m_direction : 2;
    Vec2f       m_respawnPosition;
    PlayerState m_state : 2;
    std::chrono::steady_clock::time_point m_lastShoot;
    std::chrono::steady_clock::time_point m_lastRespawn;
};