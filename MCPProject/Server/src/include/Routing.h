#pragma once
#include <crow.h>
#include <cstdint>

class Routing
{
public:
    void run();

private:
    static constexpr std::uint16_t kPort{18080};
private:
    crow::SimpleApp m_server;
};