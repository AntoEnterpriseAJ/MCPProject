#pragma once
#include "Brick.h"

class UnbreakableBrick : public Brick {
public:
    UnbreakableBrick(
        sf::Vector2f pos,
        const sf::Texture& texture,
        sf::Vector2f size = sf::Vector2f(40.0f, 40.0f)
    );

    bool isPassable() const;

private:
    bool m_isPassable;
};