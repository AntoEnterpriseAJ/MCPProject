#pragma once
#include <cstdint>
#include "nlohmann/json.hpp"

enum class GameRoomState : uint8_t
{
    Waiting,
    Playing,
    Finished
};

NLOHMANN_JSON_SERIALIZE_ENUM(GameRoomState, {
    { GameRoomState::Waiting, "Waiting" },
    { GameRoomState::Playing, "Playing" },
    { GameRoomState::Finished, "Finished" }
})