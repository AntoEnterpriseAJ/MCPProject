#include "Menu.h"

Menu::Menu()
    :
    m_currentState(MenuState::MainPage),
    m_playButton("Play", { 300, 200 }, { 200, 50 }),
    m_exitButton("Exit", { 300, 300 }, { 200, 50 }),
    m_loginButton("Login", { 300, 400 }, { 200, 50 }),
    m_registerButton("Register", { 300, 500 }, { 200, 50 }),
    m_backButton("Back", { 300, 600 }, { 200, 50 }),
    m_usernameTextBox({ 400, 50 }, { 300, 200 }, m_font, 24),
    m_passwordTextBox({ 400, 50 }, { 300, 300 }, m_font, 24)
{
    m_font.loadFromFile("res/font_text/static/Jaro_9pt-Regular.ttf");

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
    case MenuState::MainPage:             m_displayText.setString("Main Page");        break;
    case MenuState::AuthentificationPage: m_displayText.setString("Authentification"); break;
    case MenuState::RoomSelectionPage:    m_displayText.setString("Room Selection");   break;
    case MenuState::LobbyPage:            m_displayText.setString("Lobby");            break;
    }
}

void Menu::handleEvent(sf::RenderWindow& window, const sf::Event& event)
{
    switch (m_currentState)
    {
    case MenuState::MainPage:             handleMainPageEvents(window, event);             break;
    case MenuState::AuthentificationPage: handleAuthentificationPageEvents(window, event); break;
    case MenuState::RoomSelectionPage:    handleRoomSelectionPageEvents(window, event);    break;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    switch (m_currentState)
    {
    case MenuState::MainPage:             drawMainPage(window);             break;
    case MenuState::AuthentificationPage: drawAuthentificationPage(window); break;
    case MenuState::RoomSelectionPage:    drawRoomSelectionPage(window);    break;
    }
}

Menu::MenuState Menu::getState() const 
{
    return m_currentState;
}

void Menu::handleMainPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_playButton.isHovered(mousePos))
        {
            setState(MenuState::AuthentificationPage);
        }
        else if (m_exitButton.isHovered(mousePos))
        {
            window.close();
        }
    }
}

void Menu::handleAuthentificationPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    m_usernameTextBox.handleEvent(event);
    m_passwordTextBox.handleEvent(event);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_backButton.isHovered(mousePos))
        {
            setState(MenuState::MainPage);
        }

        if (m_loginButton.isHovered(mousePos))
        {
            setState(MenuState::RoomSelectionPage);
        }
    }
}

void Menu::handleRoomSelectionPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_backButton.isHovered(mousePos))
        {
            setState(MenuState::MainPage);
        }
        else if (m_playButton.isHovered(mousePos))
        {
            // TODO : Lobby state
        }
    }
}

void Menu::drawMainPage(sf::RenderWindow& window)
{
    window.draw(m_displayText);
    m_playButton.draw(window);
    m_exitButton.draw(window);
}

void Menu::drawAuthentificationPage(sf::RenderWindow& window)
{
    window.draw(m_displayText);
    m_usernameTextBox.draw(window);
    m_passwordTextBox.draw(window);
    m_loginButton.draw(window);
    m_registerButton.draw(window);
    m_backButton.draw(window);
}

void Menu::drawRoomSelectionPage(sf::RenderWindow& window)
{
    window.draw(m_displayText);
    m_backButton.draw(window);
    m_playButton.draw(window);
}
