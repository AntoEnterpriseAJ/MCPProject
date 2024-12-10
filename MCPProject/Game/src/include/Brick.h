#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"


class Brick : public GameObject
{
public:
    Brick(
        sf::Vector2f       pos, 
        const sf::Texture& texture, 
        bool               isDestroyable, 
        sf::Vector2f       size = sf::Vector2f(kBrickSize, kBrickSize)
    );

    bool isDestroyed() const;
    void hit();

    static int getSize();

private:
    static constexpr int kBrickSize = 40;

private:
    int  m_brickHealth;
    bool m_isDestroyable;
};