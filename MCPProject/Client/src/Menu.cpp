#include "Menu.h"

#include <iostream>
#include <nlohmann/json.hpp>;

#include "string"

Menu::Menu(float width, float height, NetworkManager& networkManager, uint16_t& databaseID, uint16_t& internalID)
    : m_width{width}, m_height{height}
    , m_currentState(MenuState::AuthentificationPage)
    , m_loginButton("Login", { 500 , 400 }, { 200, 50 })
    , m_registerButton("Register", { 500 , 500 }, { 200, 50 })
    , m_exitButton("Exit", { 500 , 600 }, { 200, 50 })
    , m_createRoomButton("Create Room", { 1000, 50 }, { 150, 50 })
    , m_refreshServers("Refresh", {1000, 150}, {150, 50})
    , m_backButton("Back", { 930 , 700 }, { 200, 50 })
    , m_networkManager{networkManager}
    , m_databaseID{databaseID}
    , m_internalID{internalID}
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

    m_passwordValidationMessage.setFont(m_font);
    m_passwordValidationMessage.setCharacterSize(20);
    m_passwordValidationMessage.setFillColor(sf::Color::Red);
    m_passwordValidationMessage.setPosition(450, 320);
    m_passwordValidationMessage.setString("");

    m_waitingCooldown.setFont(m_font);
    m_waitingCooldown.setString("Waiting...");
    m_waitingCooldown.setCharacterSize(30);
    m_waitingCooldown.setFillColor(sf::Color::White);
    m_waitingCooldown.setPosition(100, 50);

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
    case MenuState::AuthentificationPage: m_displayText.setString("Authentification"); break;
    case MenuState::RoomSelectionPage:    m_displayText.setString("Room Selection");   break;
    case MenuState::WaitingRoomPage:      m_displayText.setString("Waiting Room");     break;
    case MenuState::Playing:              m_displayText.setString("Playing");          break;
    }
}

void Menu::handleEvent(sf::RenderWindow& window, const sf::Event& event)
{
    switch (m_currentState)
    {
    case MenuState::AuthentificationPage: handleAuthentificationPageEvents(window, event); break;
    case MenuState::RoomSelectionPage:    handleRoomSelectionPageEvents   (window, event); break;
    case MenuState::WaitingRoomPage:      handleWaitingRoomPageEvents     (window, event); break;
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    switch (m_currentState)
    {
    case MenuState::AuthentificationPage: drawAuthentificationPage(window); break;
    case MenuState::RoomSelectionPage:    drawRoomSelectionPage   (window); break;
    case MenuState::WaitingRoomPage:      drawWaitingRoomPage     (window); break;
    }
}

bool Menu::isPlayingState()
{
    return m_currentState == MenuState::Playing;
}

void Menu::updateExistingRooms(const nlohmann::json& json)
{
    m_existingRooms.clear();
    if (json.contains("rooms") && json["rooms"].is_array()) 
    {
        int index = 1;
        for (const auto& room : json["rooms"]) 
        {
            if (room.contains("roomID") && room.contains("players")) 
            {
                int roomID = room["roomID"];
                int players = room["players"];
                m_existingRooms.emplace_back(
                    roomID, 
                    players,
                    makeLabel(roomID, players),
                    sf::Vector2f(100, 100 * index++),
                    sf::Vector2f(300, 50)
                );
            }
        }
    }
    else {
        throw std::runtime_error("Invalid JSON format: missing or incorrect 'rooms' array");
    }
}

std::string Menu::makeLabel(int id, int connectedPlayers)
{
    return "Room " + std::to_string(id) + std::string(30, ' ') + std::to_string(connectedPlayers) + "/4";
}

void Menu::backToRoomSelectionState()
{
    updateExistingRooms(m_networkManager.getExistingRooms());
    m_currentState = MenuState::RoomSelectionPage;
}

bool Menu::passwordValidator(const std::string& password)
{
    std::regex pattern("^(?=.*[A-Z])(?=.*\\d).{8,}$");

    return std::regex_match(password, pattern);
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
            if (login(m_usernameTextBox.getText(), m_passwordTextBox.getText()))
            {
                updateExistingRooms(m_networkManager.getExistingRooms());
                setState(MenuState::RoomSelectionPage);
            }
        }
        else if (m_registerButton.isHovered(mousePos))
        {
            if (passwordValidator(m_passwordTextBox.getText()))
            {
                m_passwordValidationMessage.setString("");
                if (registerUser(m_usernameTextBox.getText(), m_passwordTextBox.getText()))
                {
                    updateExistingRooms(m_networkManager.getExistingRooms());
                    setState(MenuState::RoomSelectionPage);
                }
            }
            else
            {
                m_passwordValidationMessage.setString(
                    "Password must include a number, a capital letter,\n"
                    "and be at least 8 characters long."
                );
            }
        }
        else if (m_exitButton.isHovered(mousePos))
        {
            window.close();
        }
    }
}

void Menu::handleRoomSelectionPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (const auto& room : m_existingRooms)
        {
            if (room.getButton().isHovered(mousePos))
            {
                if (!join(room.getID()))
                {
                    std::cout << "Something went wrong! Can't join on selected room!\n";
                    return;
                }
                setState(MenuState::WaitingRoomPage);
            }
        }
        if (m_createRoomButton.isHovered(mousePos))
        {
            m_networkManager.createRoom();
            if (!join(m_networkManager.getCurrentRoomID()))
            {
                std::cout << "Something went wrong! Can't join on current room!\n";
                return;
            }
            setState(MenuState::WaitingRoomPage);

        }
        else if (m_refreshServers.isHovered(mousePos))
        {
            updateExistingRooms(m_networkManager.getExistingRooms());
        }
        else if (m_backButton.isHovered(mousePos))
        {
            setState(MenuState::AuthentificationPage);
            clearTextBoxInput();
        }
    }
}

void Menu::handleWaitingRoomPageEvents(sf::RenderWindow& window, const sf::Event& event)
{
    GameRoomState gameRoomState = m_networkManager.getRoomState();
    if (gameRoomState == GameRoomState::Playing)
    {
        setState(MenuState::Playing);
    }
}

void Menu::drawAuthentificationPage(sf::RenderWindow& window)
{
    m_usernameTextBox.draw(window);
    m_passwordTextBox.draw(window);
    m_loginButton.draw(window);
    m_registerButton.draw(window);
    m_exitButton.draw(window);
    if (!m_passwordValidationMessage.getString().isEmpty())
    {
        window.draw(m_passwordValidationMessage);
    }
}

void Menu::drawRoomSelectionPage(sf::RenderWindow& window)
{
    m_createRoomButton.draw(window);
    m_refreshServers.draw(window);
    m_backButton.draw(window);

    window.draw(m_roomIdText);
    window.draw(m_playersText);

    for (auto& room : m_existingRooms)
    {
        room.getButton().draw(window);
    }
}

void Menu::drawWaitingRoomPage(sf::RenderWindow& window)
{
    window.draw(m_waitingCooldown);
}

bool Menu::login(const std::string& username, const std::string& password)
{
    nlohmann::json response = m_networkManager.login(username, password);
    if (response.empty())
    {
        std::cout << "Login failed\n";
        return false;
    }

    m_databaseID = response["databaseID"];
    std::cout << "Login successful\n";
    return true;
}

bool Menu::registerUser(const std::string& username, const std::string& password)
{
    nlohmann::json response = m_networkManager.registerUser(username, password);
    if (response.empty())
    {
        std::cout << "Register failed\n";
        return false;
    }

    m_databaseID = response["databaseID"];
    std::cout << "Register successful\n";
    return true;
}

bool Menu::join(uint8_t roomID)
{
    nlohmann::json response = m_networkManager.join(roomID, m_databaseID);

    if (response.empty())
    {
        return false;
    }

    m_internalID = response["playerID"];
    return true;
}

void Menu::clearTextBoxInput()
{
    m_usernameTextBox.setText("");
    m_passwordTextBox.setText("");
}
