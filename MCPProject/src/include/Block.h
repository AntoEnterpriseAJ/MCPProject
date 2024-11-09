#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Block : public GameObject
{
public:
    Block(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);
    virtual ~Block() = default;

    virtual bool isDestructible() const = 0;
    sf::FloatRect getBounds() const;

protected:
    int health;
};