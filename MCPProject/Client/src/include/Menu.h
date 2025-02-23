#pragma once

#include <SFML/Graphics.hpp>

import Button;
import TextBox;

#include "NetworkManager.h"
#include "Room.h"

#include <vector>
#include <cstdint>
#include <regex>
#include <string>

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
        float width,
        float height,
        NetworkManager& networkManager,
        uint16_t& databaseID,
        uint16_t& internalID
    );

    void setState   (MenuState state);
    void handleEvent(sf::RenderWindow& window, const sf::Event& event);
    void draw       (sf::RenderWindow& window);

    void updateExistingRooms(const nlohmann::json& json);
    std::string makeLabel(int id, int connectedPlayers);

    void backToRoomSelectionState();

    bool isPlayingState();
    bool passwordValidator(const std::string& password);

private:

    std::vector<Room> m_existingRooms;

    float m_width;
    float m_height;

    MenuState m_currentState;
    
    sf::Font  m_font;

    TextBox m_usernameTextBox;
    TextBox m_passwordTextBox;

    sf::Text  m_roomIdText;
    sf::Text m_playersText;
    sf::Text m_displayText;
    sf::Text m_waitingCooldown;
    sf::Text m_passwordValidationMessage;

    Button m_loginButton;
    Button m_registerButton;
    Button m_exitButton;
    Button m_createRoomButton;
    Button m_refreshServers;
    Button m_backButton;

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