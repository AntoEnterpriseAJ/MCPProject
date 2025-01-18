#include "Menu.h"

#include "string"

Menu::Menu(float width, float height)
    : m_width(width), m_height(height)
    , m_currentState    (MenuState::MainPage)
    , m_playButton      ("Play",        { 500 , 300 }, { 200, 50 })
    , m_exitButton      ("Exit",        { 500 , 400 }, { 200, 50 })
    , m_loginButton     ("Login",       { 500 , 400 }, { 200, 50 })
    , m_registerButton  ("Register",    { 500 , 500 }, { 200, 50 })
    , m_joinRoomButton  ("Join Room",   { 1000, 50  }, { 150, 50 })
    , m_createRoomButton("Create Room", { 1000, 150 }, { 150, 50 })
    , m_mainMenuButton  ("Main Menu",   { 930 , 700 }, { 200, 50 })
{
    m_font.loadFromFile("res/font_text/static/Jaro_9pt-Regular.ttf");

    m_usernameTextBox = TextBox({ 300, 50 }, { 450, 200 }, m_font, 30);
    m_passwordTextBox = TextBox({ 300, 50 }, { 450, 260 }, m_font, 30);

    m_roomIdText.setFont(m_font);
    m_roomIdText.setString("Room ID");
    m_roomIdText.setCharacterSize(30);
    m_roomIdText.setFillColor(sf::Color::White);
    m_roomIdText.setPosition(100, 50);

    m_playersText.setFont(m_font);
    m_playersText.setString("Players");
    m_playersText.setCharacterSize(30);
    m_playersText.setFillColor(sf::Color::White);
    m_playersText.setPosition(310, 50);

    m_displayText.setFont(m_font);
    m_displayText.setCharacterSize(36);
    m_displayText.setFillColor(sf::Color::Black);
    m_displayText.setPosition(100, 100);

    m_availableRooms.emplace_back(
        "Room 0                                      3/4",
        sf::Vector2f(100, 100),
        sf::Vector2f(300, 50)
    );

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
    case MenuState::MainPage:             handleMainPageEvents            (window, event); break;
    case MenuState::AuthentificationPage: handleAuthentificationPageEvents(window, event); break;
    case MenuState::RoomSelectionPage:    handleRoomSelectionPageEvents   (window, event); break;
    case MenuState::LobbyPage:            handleLobbyPageEvent            (window, event); break;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    switch (m_currentState)
    {
    case MenuState::MainPage:             drawMainPage            (window); break;
    case MenuState::AuthentificationPage: drawAuthentificationPage(window); break;
    case MenuState::RoomSelectionPage:    drawRoomSelectionPage   (window); break;
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
    m_usernameTextBox.handleEvent(event, window);
    m_passwordTextBox.handleEvent(event, window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_loginButton.isHovered(mousePos))
        {
            // TODO: Login process
            setState(MenuState::RoomSelectionPage);
        }
        if (m_registerButton.isHovered(mousePos))
        {
            // TODO: Register process
        }
        else if (m_mainMenuButton.isHovered(mousePos))
        {
            setState(MenuState::MainPage);
        }
    }
}

void Menu::handleRoomSelectionPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (m_joinRoomButton.isHovered(mousePos))
        {
            // TODO: Join a room
            setState(MenuState::LobbyPage);
        }
        else if (m_createRoomButton.isHovered(mousePos))
        {
            // TODO: Create and join a room
        }
        else if (m_mainMenuButton.isHovered(mousePos))
        {
            setState(MenuState::MainPage);
        }
    }
}

void Menu::handleLobbyPageEvent(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        //if (m_joinRoomButton.isHovered(mousePos))
        //{
        //    // TODO: Join a room
        //    setState(MenuState::LobbyPage);
        //}
        //else if (m_createRoomButton.isHovered(mousePos))
        //{
        //    // TODO: Create and join a room
        //}
        //else if (m_mainMenuButton.isHovered(mousePos))
        //{
        //    setState(MenuState::MainPage);
        //}
    }
}

void Menu::drawMainPage(sf::RenderWindow& window)
{
    m_playButton.draw(window);
    m_exitButton.draw(window);
}

void Menu::drawAuthentificationPage(sf::RenderWindow& window)
{
    m_usernameTextBox.draw(window);
    m_passwordTextBox.draw(window);
    m_loginButton.    draw(window);
    m_registerButton. draw(window);
    m_mainMenuButton. draw(window);
}

void Menu::drawRoomSelectionPage(sf::RenderWindow& window)
{
    m_joinRoomButton.  draw(window);
    m_createRoomButton.draw(window);
    m_mainMenuButton.  draw(window);

    window.draw(m_roomIdText);
    window.draw(m_playersText);

    for (const auto& room : m_availableRooms)
    {
        room.draw(window);
    }
}

void Menu::drawLobbyPage(sf::RenderWindow& window)
{
}
