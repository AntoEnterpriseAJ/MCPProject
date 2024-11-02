#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Bullet {
public:
    Bullet(float x, float y, Direction dir, float speed, const sf::Texture& texture);

    void update();
    void draw(sf::RenderWindow& window) const;
    bool getIsActive() const;
    sf::FloatRect getBounds() const;
    void setInactive();

private:
    sf::Sprite sprite;
    float speed;
    Direction direction;
    bool isActive;
};