#include "LoginWindow.h"
#include <iostream>

LoginWindow::LoginWindow(float width, float height)
    : m_isUsernameActive{ false }, m_isLoginSuccessful{ false }
{
    if (!m_font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    m_title.setFont(m_font);
    m_title.setCharacterSize(50);
    m_title.setString("Login");
    m_title.setPosition(width / 2 - m_title.getLocalBounds().width / 2, height / 2 - 150);

    m_usernameBox.setSize(sf::Vector2f(300.0f, 50.0f));
    m_usernameBox.setFillColor(sf::Color::White);
    m_usernameBox.setPosition(width / 2 - 150.0f, height / 2 - 50.0f);

    m_usernameText.setFont(m_font);
    m_usernameText.setCharacterSize(25);
    m_usernameText.setString("Username:");
    m_usernameText.setPosition(width / 2 - 150.0f, height / 2 - 100.0f);

    m_username.setFont(m_font);
    m_username.setCharacterSize(25);
    m_username.setFillColor(sf::Color::Black);
    m_username.setPosition(m_usernameBox.getPosition().x + 5, m_usernameBox.getPosition().y + 10);

    m_usernameString = "";
}

void LoginWindow::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_usernameBox);
    window.draw(m_usernameText);
    window.draw(m_username);
}

void LoginWindow::handleInput(sf::RenderWindow& window) 
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) 
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (m_usernameBox.getGlobalBounds().contains(mousePos))
            {
                m_isUsernameActive = true;
                m_usernameBox.setFillColor(sf::Color::Green);
            }
            else 
            {
                m_isUsernameActive = false;
                m_usernameBox.setFillColor(sf::Color::White);
            }
        }

        if (event.type == sf::Event::TextEntered && m_isUsernameActive) 
        {
            if (event.text.unicode == 13)
            {
                if (!m_usernameString.empty())
                {
                    m_isLoginSuccessful = true;
                }
            }
            else 
            {
                handleTextInput(event);
            }
        }
    }
}

void LoginWindow::handleTextInput(const sf::Event& event) 
{
    if (event.text.unicode >= 32 && event.text.unicode < 128) 
    {
        m_usernameString += static_cast<char>(event.text.unicode);
    }
    else if (event.text.unicode == 8 && !m_usernameString.empty())
    {
        m_usernameString.pop_back();
    }

    m_username.setString(m_usernameString);
}

bool LoginWindow::isLoginSuccessful() const 
{
    return m_isLoginSuccessful;
}

std::string LoginWindow::getUsername()
{
    return m_usernameString;
}
