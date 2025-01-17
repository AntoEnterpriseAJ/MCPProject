export module Game;

import <SFML/Graphics.hpp>;
import <cstdint>;
import <unordered_map>;
import <string>;
import <string_view>;
import <cpr/cpr.h>;
import "Player.h";
import "NetworkManager.h";
import "BulletManager.h";
import "PowerUpManager.h";
import Level;

export class Game
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
    void handleInputs(float deltaTime);
    void createRoom();
    bool join(uint8_t roomID);
    void update();
    void move(Direction direction, float deltaTime);
    void displayRooms();
    void handleMenu();
private:
    static constexpr uint16_t kWindowWidth{ 1200 };
    static constexpr uint16_t kWindowHeight{ 800 };
private:
    std::unordered_map<uint16_t, Player> m_players;
    sf::Clock              m_lastFrametimeClock;
    Level                  m_level;
    NetworkManager         m_networkManager;
    PowerUpManager         m_powerUpManager;
    BulletManager          m_bulletManager;
    uint16_t               m_internalID;
    GameState              m_gameState;
    sf::RenderWindow       m_window;
};