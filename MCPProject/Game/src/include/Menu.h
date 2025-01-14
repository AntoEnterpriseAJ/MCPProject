
#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "TextBox.h"

class Menu {
public:
    enum class MenuState 
    {
        MainPage,
        AuthentificationPage,
        RoomSelectionPage,
        LobbyPage
    };

    Menu();

    void setState(MenuState state);
    void handleEvent(sf::RenderWindow& window, const sf::Event& event);
    void draw(sf::RenderWindow& window);

    MenuState getState() const;

private:
    MenuState m_currentState;
    sf::Text  m_displayText;
    sf::Font  m_font;

    Button m_playButton;
    Button m_exitButton;

    Button  m_loginButton;
    Button  m_registerButton;
    Button  m_backButton;
    TextBox m_usernameTextBox;
    TextBox m_passwordTextBox;

    void handleMainPageEvents            (sf::RenderWindow& window, const sf::Event& event);
    void handleAuthentificationPageEvents(sf::RenderWindow& window, const sf::Event& event);
    void handleRoomSelectionPageEvents   (sf::RenderWindow& window, const sf::Event& event);

    void drawMainPage            (sf::RenderWindow& window);
    void drawAuthentificationPage(sf::RenderWindow& window);
    void drawRoomSelectionPage   (sf::RenderWindow& window);
};