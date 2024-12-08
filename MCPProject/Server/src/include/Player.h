#pragma once
#include <utility>

class Player
{
public:
    using Position = std::pair<int, int>;

    Player(Position position);

    Position getPosition() const;

private:
    Position m_position;
};