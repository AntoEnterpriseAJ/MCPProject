#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "GameObject.h"
#include "Direction.h"
#include "Bullet.h"
#include "Brick.h"
#include "Bush.h"
#include <variant>

class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    Direction getDirection() const;

    void update(float deltaTime);
    void restartCooldown();
    
    bool canShoot() const;
    bool canMove(const std::vector<std::variant<Brick, Bush>>& levelLayout, float deltaTime);
    void movePlayer(const std::vector<std::variant<Brick, Bush>>& levelLayout, float deltaTime);

private:
    float             m_health;
    Direction         m_direction    : 2;


    float                  m_cooldownDuration;
    static constexpr float kCooldownTime = 0.5f;
    static constexpr float kPlayerSpeed = 150.15f;

};