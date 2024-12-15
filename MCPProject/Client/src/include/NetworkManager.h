#pragma once
#include <Player.h>
#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

class NetworkManager
{
public:
    NetworkManager();

    nlohmann::json join(const Player& player);
    nlohmann::json update();
    void movePlayer(uint16_t clientID, Direction direction);

private:
    static const std::string kServerUrl;
private:
    cpr::Session m_session;
    uint32_t     m_clientVersion;
};