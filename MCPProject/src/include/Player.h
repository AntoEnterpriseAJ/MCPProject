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

    void movePlayer(const std::vector<Brick>& bricks);
    void restartTimer();
    // TODO: think about how we're gonna handle the texture loading
    //       textures should load ONLY ONCE per game, not every time we shoot
    //       ResourceManager singleton class?
    void shoot(const sf::Texture& bulletTexture);

    //TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
    void movePlayer(const std::vector<std::variant<Brick, Bush>>& levelLayout);

    //TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
    void updateBullets(std::vector<std::variant<Brick, Bush>>& levelLayout);

    bool canMove(Direction direction, const std::vector<std::variant<Brick, Bush>>& levelLayout);

    std::list<Bullet>& getBullets();

    void updateTimer();

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