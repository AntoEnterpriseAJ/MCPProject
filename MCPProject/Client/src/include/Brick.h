#pragma once
#include "Obstacle.h"

class Brick : public Obstacle
{
public:
    Brick(
        const sf::Vector2f& pos,
        const sf::Texture& texture,
        int health = 3,
        bool passable = false,
        bool destroyable = true
    );

    ~Brick() override = default;

    bool isDestroyed() const noexcept;
    void hit();

private:
    int m_brickHealth;
};