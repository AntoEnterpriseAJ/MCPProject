#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Direction.h"

class Bullet; // Forward declaration

class Player : public GameObject
{
public:
    Player(sf::RectangleShape rect);

    sf::RectangleShape getPlayerShape();

    void movePlayer(sf::Event event);

    void shoot();

    void updateBullets();

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    void setColor(const sf::Color& color);

    std::vector<Bullet>& getBullets();

private:
    sf::Color m_color;
    sf::RectangleShape m_rectangle;
    std::vector<Bullet> bullets;
    Direction dir = Direction::UP; // Initial Direction
};
