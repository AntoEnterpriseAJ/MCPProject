#pragma once
#include <utility>
#include "Direction.h"

class Player
{
public:
    struct Position
    {
        float x;
        float y;
    };
public:

    Player() = default;
    Player(const Position& position, Direction direcion = Direction::Left);

    void move(Direction direction, float deltaTime);

    Direction getDirection() const;
    Position getPosition() const;
private:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;
private:
    Position  m_position;
    Direction m_direction;
};