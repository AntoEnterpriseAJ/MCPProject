#pragma once
#include "Obstacle.h"

class BombBrick : public Obstacle
{
public:
    BombBrick(
        const sf::Vector2f& pos,
        const sf::Texture& texture,
        int explosionRadius = 3
    );

    ~BombBrick() override = default;

    int getExplosionRadius() const noexcept;

private:
    int m_explosionRadius;
};
