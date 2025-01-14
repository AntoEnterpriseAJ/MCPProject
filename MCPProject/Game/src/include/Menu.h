
#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "TextBox.h"

class Menu {
public:
    enum class MenuState 
    {
        MainPage,
        Authentification,
        RoomSelection,
        Lobby
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
    Button    m_playButton;
    Button    m_exitButton;

    void handleMainPageEvents(sf::RenderWindow& window, const sf::Event& event);
};