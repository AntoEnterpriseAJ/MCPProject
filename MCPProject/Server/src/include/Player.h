#pragma once
#include "GameObject.h"
#include "Direction.h"

class Player : public GameObject
{
public:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;
public:
    Player() = default;
    Player(
        const Vec2f& position,
        const Vec2f& size = {kPlayerSizeX, kPlayerSizeY},
        Direction direcion = Direction::Left
    );
    ~Player() override = default;

    void setDirection(Direction direction);
    void restartCooldown();

    bool canShoot() const;
    Direction getDirection() const;
public:
    static constexpr float kPlayerSizeX = 39.9f;
    static constexpr float kPlayerSizeY = 39.9f;
private:
    Direction m_direction : 2;
    std::chrono::steady_clock::time_point m_lastUpdated;
};