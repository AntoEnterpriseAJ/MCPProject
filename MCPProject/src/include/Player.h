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
    Player(const sf::Texture& texture);

    void movePlayer();

    void shoot();

    void updateBullets();

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    std::vector<Bullet>& getBullets();

    void draw(sf::RenderWindow& window);

private:
    sf::Sprite m_sprite;
    std::vector<Bullet> bullets;
    Direction dir = Direction::UP;
};
