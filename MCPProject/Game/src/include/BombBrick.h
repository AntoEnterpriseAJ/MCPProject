#pragma once

#include "Obstacle.h"

class BombBrick : public Obstacle
{
public:
    BombBrick(sf::Vector2f pos, const sf::Texture& texture);

    int GetExplosionRadius();

private:
    int m_explosionRadius;
};