#pragma once
#include <crow.h>
#include <cstdint>
#include <vector>
#include "Player.h"

class Routing
{
public:
    Routing();

    void run();

private:
    static constexpr std::uint16_t kPort{18080};
    static constexpr std::uint32_t kMaxVersion{1000000};
private:
    uint16_t m_idCounter;
    uint32_t m_version;
    crow::SimpleApp m_server;
    std::unordered_map<uint16_t, Player> m_players;
};