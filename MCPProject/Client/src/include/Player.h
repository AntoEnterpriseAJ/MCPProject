#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Direction.h"

class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);
    ~Player() override = default;

    Direction getDirection() const;

private:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;
private:
    float     m_health;
    Direction m_direction : 2;
};