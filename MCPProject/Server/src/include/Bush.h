#pragma once
#include "Obstacle.h"
#include "Vec2f.h"

class Bush : public Obstacle
{
public:
    Bush(const Vec2f& pos);
    ~Bush() override = default;

    bool isPassable() const;

private:
    bool m_isPassable;
};