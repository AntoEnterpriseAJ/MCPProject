#pragma once
#include "Obstacle.h"

class Bush : public Obstacle
{
public:
    Bush(
        const sf::Vector2f& pos,
        const sf::Texture& texture
    );

    ~Bush() override = default;
private:
    /*same as Obstacle*/
};
