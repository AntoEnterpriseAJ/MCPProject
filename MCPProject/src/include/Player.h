#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "GameObject.h"
#include "Direction.h"
#include "Bullet.h"
#include "Brick.h"

// TODO: should the player handle it's own input?
class Player : public GameObject
{
public:
    Player() = default;
    Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    // TODO: think about how we're gonna handle the texture loading
    //       textures should load ONLY ONCE per game, not every time we shoot
    //       ResourceManager singleton class?
    void shoot(const sf::Texture& bulletTexture);

    //TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
    void movePlayer(const std::vector<Brick>& bricks);

    //TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
    void updateBullets(std::vector<Brick>& bricks);

    bool canMove(Direction direction, const std::vector<Brick>& bricks);

    std::list<Bullet>& getBullets();

    void updateTimer();

private:
    float             m_health;
    std::list<Bullet> m_bullets;
    Direction         m_dir;

    sf::Clock m_cooldownClock;
    float     m_cooldownDuration;
    bool      m_canShoot;

    float kPlayerSpeed { 0.15f };
};