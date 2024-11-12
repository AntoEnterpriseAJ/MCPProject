#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "Bullet.h"

static constexpr uint16_t kWindowWidth = 1200;
static constexpr uint16_t kWindowHeight = 800;

class Game
{
public:
    Game();

    void render();
    void handleInputs();

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();

private:
    Player m_player; //TODO: vector of players for multiplayer
    std::vector<Bullet> m_bullets; 
    sf::RenderWindow m_window;
    Level m_level;
};