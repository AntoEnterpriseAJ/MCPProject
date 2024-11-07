#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "Bullet.h"

class Game
{
public:

    Game(uint16_t windowWidth, uint16_t windowHeight);

    void render();
    void handleInputs();

private:
    Player m_player; //TODO: vector of players for multiplayer
    std::vector<Bullet> m_bullets; 
    sf::RenderWindow m_window;
    Level m_level;
};