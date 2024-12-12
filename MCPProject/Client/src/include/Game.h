#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include <unordered_map>
#include <string>
#include <string_view>

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

    static uint16_t getWindowWidth();
    static uint16_t getWindowHeight();
private:
    void join(sf::Vector2f position);
    void update();
    void move(Direction direction);
private:
    static constexpr uint16_t kWindowWidth{ 1200 };
    static constexpr uint16_t kWindowHeight{ 800 };
private:
    std::unordered_map<uint16_t, Player> m_players;
    uint16_t               m_internalID;
    GameState              m_gameState;
    sf::RenderWindow       m_window;
};