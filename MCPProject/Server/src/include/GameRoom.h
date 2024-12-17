#pragma once
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Player.h"

class GameRoom
{
public:
    GameRoom() = default;
    GameRoom(uint8_t m_roomID);

    uint8_t addPlayer(const Player::Position& position);
    nlohmann::json getStateResponse(uint32_t clientVersion) const noexcept;
    void move(uint8_t playerID, Direction direction, float deltaTime);

    uint32_t getVersion() const noexcept;
    uint8_t getID() const noexcept;
    const std::unordered_map<uint8_t, Player>& getPlayers() const noexcept;


private:
    static constexpr uint32_t kMaxVersion{1000000};
private:
    uint8_t  m_roomID;
    uint8_t  m_idCounter;
    uint32_t m_version;
    std::unordered_map<uint8_t, Player> m_players;
};