
#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "TextBox.h"
#include <regex>
#include <string>
#include <vector>
#include <iostream>

class Menu {
public:
    enum class MenuState 
    {
        MainPage,
        AuthentificationPage,
        RoomSelectionPage,
        LobbyPage
    };

    Menu(float width, float height);

    void setState(MenuState state);
    void handleEvent(sf::RenderWindow& window, const sf::Event& event);
    void draw(sf::RenderWindow& window);

    bool passwordValidator(const std::string& password);


    MenuState getState() const;

private:
    float m_width;
    float m_height;

    MenuState m_currentState;
    sf::Text  m_displayText;
    sf::Font  m_font;
    sf::Text m_passwordValidationMessage;


    Button m_playButton;
    Button m_exitButton;

    Button  m_loginButton;
    Button  m_registerButton;
    TextBox m_usernameTextBox;
    TextBox m_passwordTextBox;

    Button              m_joinRoomButton;
    Button              m_createRoomButton;
    sf::Text            m_roomIdText;
    sf::Text            m_playersText;
    std::vector<Button> m_availableRooms;

    Button m_mainMenuButton;

    void handleMainPageEvents            (sf::RenderWindow& window, const sf::Event& event);
    void handleAuthentificationPageEvents(sf::RenderWindow& window, const sf::Event& event);
    void handleRoomSelectionPageEvents   (sf::RenderWindow& window, const sf::Event& event);
    void handleLobbyPageEvent            (sf::RenderWindow& window, const sf::Event& event);

    void drawMainPage            (sf::RenderWindow& window);
    void drawAuthentificationPage(sf::RenderWindow& window);
    void drawRoomSelectionPage   (sf::RenderWindow& window);
    void drawLobbyPage           (sf::RenderWindow& window);
};