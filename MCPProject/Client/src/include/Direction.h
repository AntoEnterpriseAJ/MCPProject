#pragma once
#include <nlohmann/json.hpp>

enum class Direction : uint8_t
{
    Up,
    Down,
    Left,
    Right
};

NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
    {Direction::Up, "up"},
    {Direction::Down, "down"},
    {Direction::Left, "left"},
    {Direction::Right, "right"}
})