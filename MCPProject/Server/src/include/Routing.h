#pragma once
#include <crow.h>
#include <cstdint>
#include <vector>
#include "Player.h"
#include "GameRoom.h"

class Routing
{
public:
    Routing();

    void run();

private:
    static constexpr std::uint16_t kPort{18080};
private:
    std::unordered_map<uint8_t, GameRoom> m_rooms; 
    crow::SimpleApp m_server;
    uint8_t m_roomIDCounter;
};