#pragma once
#include "GameObject.h"
#include "ObstacleType.h"
#include "Vec2f.h"

class Obstacle : public GameObject
{
public:
    Obstacle(
        const Vec2f&  pos,
        const Vec2f&  size,
        bool          passable,
        bool          destroyable
    );

    ~Obstacle() override = default;

    bool isPassable() const;
    bool isDestroyable() const; 

public:
    static constexpr float kObstacleSize{40.0f};
protected:
    bool m_isDestroyable;
    bool m_isPassable;
};