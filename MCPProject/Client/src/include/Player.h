#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Direction.h"

class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    Direction getDirection() const;

    void update(float deltaTime);
    bool canShoot() const;
    void restartCooldown();
    
    //bool canMove(const Level& level, float deltaTime);
    //void movePlayer(const Level& level, float deltaTime);

private:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;
private:
    float     m_health;
    float     m_cooldownDuration;
    Direction m_direction : 2;
};