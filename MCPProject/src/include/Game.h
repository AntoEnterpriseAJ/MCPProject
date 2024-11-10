#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "Bullet.h"

class Game
{
public:

    Game();

    void render();
    void handleInputs();

private:
    Player m_player; //TODO: vector of players for multiplayer
    std::vector<Bullet> m_bullets; 
    sf::RenderWindow m_window;
    Level m_level;

    static constexpr uint16_t m_windowWidth = 1200;
    static constexpr uint16_t m_windowHeight = 800;
};