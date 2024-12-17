#pragma once
#include <Player.h>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "URL.h"

class NetworkManager
{
public:
    NetworkManager();

    void createRoom();
    nlohmann::json join(const Player& player, uint8_t roomID);
    nlohmann::json update();
    nlohmann::json getExistingRooms();
    void movePlayer(uint16_t clientID, Direction direction, float deltaTime);

    void setRoomID(uint8_t roomID);
    uint8_t getCurrentRoomID() const;

private:
    static const std::string kServerUrl;
private:
    uint8_t      m_currentRoomID;
    cpr::Session m_session;
    uint32_t     m_clientVersion;
    URL          m_URL;
};