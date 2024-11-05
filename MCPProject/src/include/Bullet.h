#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    enum class State
    {
        Active,
        Inactive,
    };
public:

    Bullet(sf::Vector2f pos, const sf::Texture& texture, Direction,
           sf::Vector2f size = sf::Vector2f(kBulletSizeX, kBulletSizeY));

    void update();
    void setState(State state);
    
    State getState() const;

private:
    //TODO: sf::Vector2f doesn't support static constexpr initialization
    //static constexpr sf::Vector2f bulletSize = sf::Vector2f(500.0f, 500.0f);
    //Switch to GLM or there's a chance it supports in SFML 3.0
    static constexpr float kBulletSizeX = 50.0f;
    static constexpr float kBulletSizeY = 50.0f;
    static constexpr float kBulletSpeed = 5.0f;
private:
    Direction m_direction;
    State     m_state;
};