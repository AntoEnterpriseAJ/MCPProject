#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "TextBox.h"
#include "NetworkManager.h"
#include "Room.h"

#include <vector>
#include <cstdint>

class Menu {
public:
    enum class MenuState
    {
        AuthentificationPage,
        RoomSelectionPage,
        WaitingRoomPage,
        Playing
    };

    Menu(
          float width
        , float height
        , NetworkManager& networkManager
        , uint16_t& databaseID
        , uint16_t& internalID
    );

    void setState(MenuState state);
    void handleEvent(sf::RenderWindow& window, const sf::Event& event);
    void draw(sf::RenderWindow& window);

    bool isPlayingState();

    void updateExistingRooms(const nlohmann::json& json);
    std::string makeLabel(int id, int connectedPlayers);

    void backToRoomSelectionState();

private:
    std::vector<Room> m_existingRooms;

    float m_width;
    float m_height;

    MenuState m_currentState;
    sf::Text  m_displayText;
    sf::Font  m_font;

    // Login / Register Page buttons and textboxs
    Button  m_loginButton;
    Button  m_registerButton;
    Button  m_exitButton;
    TextBox m_usernameTextBox;
    TextBox m_passwordTextBox;

    // Room Selection Page buttons, text and list of available rooms
    Button              m_createRoomButton;
    Button              m_refreshServers;
    sf::Text            m_roomIdText;
    sf::Text            m_playersText;
    Button              m_backButton;

    // Waiting room cooldown
    sf::Text m_waitingCooldown;

    // Network and database related members
    NetworkManager& m_networkManager;
    uint16_t& m_databaseID;
    uint16_t& m_internalID;

private:
    void handleAuthentificationPageEvents(sf::RenderWindow& window, const sf::Event& event);
    void handleRoomSelectionPageEvents   (sf::RenderWindow& window, const sf::Event& event);
    void handleWaitingRoomPageEvents     (sf::RenderWindow& window, const sf::Event& event);

    void drawAuthentificationPage(sf::RenderWindow& window);
    void drawRoomSelectionPage   (sf::RenderWindow& window);
    void drawWaitingRoomPage     (sf::RenderWindow& window);

    bool login       (const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
    bool join(uint8_t roomID);

    void clearTextBoxInput();
};