#pragma once

#include "GameObject.h"

class Obstacle : public GameObject
{
public:
    Obstacle(
        const sf::Vector2f&  pos,
        const sf::Texture&   texture,
        const sf::Vector2f&  size,
        bool                 passable,
        bool                 destroyable
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