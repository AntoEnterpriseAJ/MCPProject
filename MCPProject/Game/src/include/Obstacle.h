#pragma once

#include "GameObject.h"

class Obstacle : public GameObject
{
public:
    Obstacle(
        sf::Vector2f       pos,
        const sf::Texture& texture,
        bool               isPassable,
        bool               isDestroyable,
        sf::Vector2f       size = sf::Vector2f(kObstacleSize, kObstacleSize)
    );

    bool isPassable();
    bool isDestroyable();

    static float getObstacleSize();

protected:
    static constexpr int kObstacleSize = 40;

protected:
    bool m_isDestroyable;
    bool m_isPassable;
};