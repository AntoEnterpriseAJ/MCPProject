#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "BulletManager.h"


class Game
{
public:
    Game();

    void render();
    void handleInputs();

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();

private:
    //void drawGrid();
private:
    static constexpr uint16_t kWindowWidth = 1200;
    static constexpr uint16_t kWindowHeight = 800;
private:
    Player m_player; //TODO: vector of players for multiplayer
    std::vector<Bullet> m_bullets;
    sf::RenderWindow m_window;
    Level m_level;
    //BulletManager m_bulletManager;
};