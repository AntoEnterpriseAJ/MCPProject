#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

static constexpr int kBrickSize = 40;

class Brick : public GameObject
{
public:
    Brick(
        sf::Vector2f       pos, 
        const sf::Texture& texture, 
        bool               isDestroyable, 
        sf::Vector2f       size = sf::Vector2f(kBrickSize, kBrickSize)
    );

    static int getSize();

    bool isDestroyed() const;
    void hit();

    bool isInArea(
        const sf::Vector2f& upLeft, 
        const sf::Vector2f& downRight
    );

    sf::FloatRect getBounds() const;

    bool operator==(const Brick& other) const;

private:
    bool m_isDestroyable   { false };
    int  m_brickHealth     { 3 };
    int  m_explosionRadius { 3 };
};