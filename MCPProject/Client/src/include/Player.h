#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Direction.h"
#include "PlayerState.h"

class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);
    ~Player() override = default;

    void Update(float deltaTime);
    void setDirection(Direction direction);
    void setLives(uint16_t lives);
    void setHealth(uint16_t health);
    void setState(PlayerState state);
    void setPoints(uint16_t points);

    void move(Direction direction, float deltaTime);
    void resetShootCooldown();

    bool        isAlive() const;
    bool        canShoot() const;
    Direction   GetDirection() const;
    PlayerState GetState() const;
    uint16_t    GetLives() const;
    uint16_t    GetHealth() const;
    uint16_t    GetPoints() const;

private:
    static constexpr float    kCooldownTime = 0.5f;
    static constexpr float    kPlayerSpeed  = 150.0f;
    static constexpr uint16_t kPlayerHealth = 100.0f;
    static constexpr uint16_t kPlayerLives  = 3;

private:
    float       m_timeElapsed; 
    uint16_t    m_lives;
    uint16_t    m_health;
    uint16_t    m_points;
    PlayerState m_state : 2;
    Direction   m_direction : 2;
};