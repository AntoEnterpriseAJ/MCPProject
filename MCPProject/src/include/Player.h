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

    bool canShoot() const;
    Direction getDirection() const;

    void restartTimer();
    bool canMove(Direction direction, const std::vector<std::variant<Brick, Bush>>& levelLayout);
    void movePlayer(const std::vector<std::variant<Brick, Bush>>& levelLayout);
private:
    float             m_health;
    Direction         m_dir : 2;

    // TODO: should the player hold the cooldown timer?
    sf::Clock m_cooldownClock;
    float     m_cooldownDuration;

    float kPlayerSpeed { 0.15f };
};