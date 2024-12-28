#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Direction.h"
#include "Level.h"

class Player : public GameObject
{

public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    Direction GetDirection() const;

    void Update(float deltaTime);
    void RestartCooldown();
    
    bool CanShoot() const;
    bool CanMove(const Level& level, float deltaTime);
    void MovePlayer(const Level& level, float deltaTime);

private:
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.0f;

private:
    float     m_health;
    float     m_cooldownDuration;
    Direction m_direction : 2;
};