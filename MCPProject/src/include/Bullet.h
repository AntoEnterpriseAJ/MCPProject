#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Bullet {
public:
    Bullet(int x, int y, Direction dir, float speed);

    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool getIsActive() const;
    int getX() const;
    int getY() const;

private:
    sf::RectangleShape m_shape;
    Direction m_direction;
    float m_speed;
    bool m_active;
};
