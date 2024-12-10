#pragma once
#include "SFML/Graphics.hpp"
#include "Obstacle.h"


class Brick : public Obstacle
{
public:
    Brick(sf::Vector2f pos, const sf::Texture& texture);

    bool isDestroyed() const;
    void hit();

private:
    int  m_brickHealth;
    bool m_isDestroyable;
};