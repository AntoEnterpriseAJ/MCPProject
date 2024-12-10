#pragma once
#include "SFML/Graphics.hpp"
#include "Obstacle.h"

class Bush : public Obstacle
{
public:
    Bush(sf::Vector2f pos, const sf::Texture& texture);

    bool isPassable() const;

private:
    bool m_isPassable;
};