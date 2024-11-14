#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"


//  TODO: player move under the bush
class Bush : public GameObject
{
public:
    Bush(
        sf::Vector2f pos,
        const sf::Texture& texture,
        sf::Vector2f size = sf::Vector2f(40.0f, 40.0f)
    );

    bool isPassable() const;
    sf::FloatRect getBounds() const;

    bool operator==(const Bush& other) const;

private:
    bool m_isPassable{ true }; // Bushurile sunt traversabile
};