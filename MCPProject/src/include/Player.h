#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "GameObject.h"
#include "Direction.h"
#include "Bullet.h"
#include "Brick.h"

class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    void movePlayer(const std::vector<Brick>& bricks);
    void restartTimer();

    Direction getDirection() const;
    bool canShoot() const;
    bool canMove(Direction direction, const std::vector<Brick>& bricks) const;
private:
    float             m_health;
    std::list<Bullet> m_bullets;
    Direction         m_dir : 2;

    // TODO: should the player hold the cooldown timer?
    sf::Clock m_cooldownClock;
    float     m_cooldownDuration;

    float kPlayerSpeed { 0.15f };
};