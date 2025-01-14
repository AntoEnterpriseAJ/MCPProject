#include "Menu.h"

Menu::Menu()
    : 
    m_currentState(MenuState::MainPage),
    m_playButton("Play", { 300, 200 }, { 200, 50 }),
    m_exitButton("Exit", { 300, 300 }, { 200, 50 })
{
    sf::Font font;
    font.loadFromFile("res/font_text/static/Jaro_9pt-Regular.ttf");

    m_displayText.setFont(m_font);
    m_displayText.setCharacterSize(36);
    m_displayText.setFillColor(sf::Color::Black);
    m_displayText.setPosition(100, 100);

    setState(m_currentState);
}

void Menu::setState(MenuState state) 
{
    m_currentState = state;

    switch (state) 
    {
    case MenuState::MainPage:         m_displayText.setString("Main Page");        break;
    case MenuState::Authentification: m_displayText.setString("Authentification"); break;
    case MenuState::RoomSelection:    m_displayText.setString("Room Selection");   break;
    case MenuState::Lobby:            m_displayText.setString("Lobby");            break;
    }
}

void Menu::handleEvent(sf::RenderWindow& window, const sf::Event& event) 
{
    if (m_currentState == MenuState::MainPage) 
    {
        handleMainPageEvents(window, event);
    }
}

void Menu::handleMainPageEvents(sf::RenderWindow& window, const sf::Event& event) 
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_playButton.isHovered(mousePos)) 
        {
            // TODO : switch to authentification menu state
        }
        else if (m_exitButton.isHovered(mousePos))
        {
            window.close();
        }
    }
}

void Menu::draw(sf::RenderWindow& window) 
{
    if (m_currentState == MenuState::MainPage) 
    {
        window.draw(m_displayText);
        m_playButton.draw(window);
        m_exitButton.draw(window);
    }
}

Menu::MenuState Menu::getState() const 
{
    return m_currentState;
}
