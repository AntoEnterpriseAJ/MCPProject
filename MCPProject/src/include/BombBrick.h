#pragma once

#include "Brick.h"

class BombBrick : public Brick
{
public:
    BombBrick(
        sf::Vector2f       pos,
        const sf::Texture& texture,
        bool               isDestroyable,
        sf::Vector2f       size = sf::Vector2f(Brick::getSize(), Brick::getSize())
    );

	void destroyInArea(const sf::Vector2f& centerExplosionPosition);

private:
    int  m_explosionRadius{ 3 };
};