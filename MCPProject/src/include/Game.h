#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "BulletManager.h"
#include "BrickManager.h"


class Game
{
public:
    Game();

    void render();
    void handleInputs(float deltaTime);
    void insertPlayer(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();

private:
    void drawGrid();
private:
    static constexpr uint16_t kWindowWidth  { 1200 };
    static constexpr uint16_t kWindowHeight { 800  };
private:
    sf::Clock           m_lastFrameTimeClock;
    std::vector<Player> m_players; 
    sf::RenderWindow    m_window;
    Level               m_level;
    BulletManager       m_bulletManager;
};