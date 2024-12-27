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
        const Vec2f& size = {39.9f, 39.9f},
        Direction direcion = Direction::Left
    );
    ~Player() override = default;

    void setDirection(Direction direction);

    Direction getDirection() const;
private:
    Direction m_direction : 2;
};