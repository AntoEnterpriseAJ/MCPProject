#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    enum class State : uint8_t
    {
        Active,
        Inactive,
    };

public:

    Bullet(
        sf::Vector2f       pos, 
        const sf::Texture& texture, 
        Direction,
        sf::Vector2f       size = sf::Vector2f(kBulletSizeX, kBulletSizeY)
    );

    void setState(State state);
    void move(float offsetX, float offsetY);

    Direction getDirection() const;
    State getState() const;

    static constexpr float kBulletSpeed { 0.6f };
private:
    static constexpr float kBulletSizeX { 20.0f };
    static constexpr float kBulletSizeY { 50.0f };
private:
    Direction m_direction : 2;
    State     m_state     : 1;
};