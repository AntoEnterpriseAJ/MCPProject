#pragma once
#include <utility>

class Player
{
public:
    using Position = std::pair<float, float>;

    Player() = default;
    Player(const Position& position, uint16_t id);

    void setPosition(const Position& position);

    Position getPosition() const;
private:
    Position m_position;
};