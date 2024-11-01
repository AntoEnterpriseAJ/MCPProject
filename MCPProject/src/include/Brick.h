#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Brick : public GameObject
{
public:
    Brick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size = sf::Vector2f(m_brickSize, m_brickSize));
    static int getSize();

private:
    static const int m_brickSize = 30;
};
