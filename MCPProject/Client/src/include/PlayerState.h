#pragma once
#include <nlohmann/json.hpp>
#include <cstdint>

enum class PlayerState : uint8_t
{
    Alive,
    Respawning,
    Eliminated
};

NLOHMANN_JSON_SERIALIZE_ENUM(PlayerState, {
    {PlayerState::Alive, "alive"},
    {PlayerState::Respawning, "respawning"},
    {PlayerState::Eliminated, "eliminated"}
})  