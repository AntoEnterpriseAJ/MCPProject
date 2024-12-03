#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include "Player.h"
#include "Level.h"
#include "BulletManager.h"
#include "Menu.h"
#include "LoginWindow.h"
#include "RegisterWindow.h"


class Game
{
public:
    enum class GameState
    {
        Menu,
        Playing,
        Login,
        Register
    };

    Game();

    void render();
    void handleInputs(float deltaTime);
    void insertPlayer(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size);

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();

private:
    void drawGrid();
private:
    static constexpr uint16_t kWindowWidth{ 1200 };
    static constexpr uint16_t kWindowHeight{ 800 };
private:
    GameState              m_gameState;
    sf::Clock              m_lastFrameTimeClock;
    std::vector<Player>    m_players;
    sf::RenderWindow       m_window;
    Menu                   m_menu;
    Level                  m_level;
    BulletManager          m_bulletManager;
    sf::Music              m_backgroundMusic;
private:
    void renderMenu();
    void renderLogin(LoginWindow& loginWindow);
    void renderRegister(RegisterWindow& registerWindow);
    void renderGame(float deltaTime);
};