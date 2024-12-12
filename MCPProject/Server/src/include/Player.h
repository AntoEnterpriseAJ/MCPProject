#pragma once
#include <utility>

class Player
{
public:
    using Position = std::pair<uint16_t, uint16_t>;

    Player(const Position& position, uint16_t id);

    Position getPosition() const;
    uint16_t getID() const;

private:
    Position m_position;
    uint16_t m_id;
};