#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "GameObject.h"
#include "Direction.h"
#include "Brick.h"

class Bullet; // Forward declaration

class Player : public GameObject
{
public:
    Player(const sf::Texture& texture, const sf::Texture& bulletTexture);

    void movePlayer();
    void shoot();
    void updateBullets(const std::vector<Brick>& bricks);

    void draw(sf::RenderWindow& window);

    std::vector<Bullet>& getBullets();

private:
    sf::Sprite m_sprite;
    std::vector<Bullet> bullets;
    Direction dir = Direction::UP;
    const sf::Texture& bulletTexture;
};