#pragma once

#include <SFML/Graphics.hpp>;
#include <cstdint>;
#include <unordered_map>;
#include <string>;
#include <string_view>;
#include <cpr/cpr.h>;
#include "Player.h";
#include "NetworkManager.h";
#include "BulletManager.h";
#include "PowerUpManager.h";
#include "Level.h";
#include "Menu.h";

class Game
{
public:
    enum class GameState
    {
        Menu,
        Waiting,
        Authentificate,
        Playing,
    };

    Game();

    void render();

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();

private:
    void handleInputs(float deltaTime);
    void createRoom();
    void buyPowerUp(PowerUpEffect powerUp);
    bool join(uint8_t roomID);
    bool login(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    void update();
    void move(Direction direction, float deltaTime);
    void displayRooms();
    void handleMenu();
    void handleRoomWaiting();
    void handleAuthentification();

private:
    static constexpr uint16_t kWindowWidth{ 1200 };
    static constexpr uint16_t kWindowHeight{ 800 };

private:
    std::unordered_map<uint16_t, Player> m_players;

    GameState        m_gameState;
    sf::Clock        m_lastFrametimeClock;
    Level            m_level;
    NetworkManager   m_networkManager;
    PowerUpManager   m_powerUpManager;
    BulletManager    m_bulletManager;
    uint16_t         m_internalID;
    uint16_t         m_databaseID;
    sf::RenderWindow m_window;
};