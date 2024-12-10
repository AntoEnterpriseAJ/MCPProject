#pragma once
#include "Obstacle.h"

class UnbreakableBrick : public Obstacle 
{
public:
    UnbreakableBrick(
        sf::Vector2f       pos,
        const sf::Texture& texture
    );
};