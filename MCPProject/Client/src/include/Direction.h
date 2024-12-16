#pragma once
#include <nlohmann/json.hpp>

enum class Direction : uint8_t
{
    Up,
    Down,
    Left,
    Right
};

// TODO: maybe namespace it
constexpr float getRotation(Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        return 0.0f;
    case Direction::Down:
        return 180.0f;
    case Direction::Left:
        return 270.0f;
    case Direction::Right:
        return 90.0f;
    }
}

NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
    {Direction::Up, "up"},
    {Direction::Down, "down"},
    {Direction::Left, "left"},
    {Direction::Right, "right"}
})