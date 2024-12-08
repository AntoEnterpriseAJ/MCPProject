#include "LoginWindow.h"
#include <iostream>

LoginWindow::LoginWindow(float width, float height)
    : m_isUsernameActive{ false }, m_isPasswordActive{ false }, m_passwordValue{} {
    if (!m_font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    m_title.setFont(m_font);
    m_title.setCharacterSize(50);
    m_title.setString("Login");
    m_title.setPosition(width / 2 - m_title.getLocalBounds().width / 2, height / 2 - 200);

    m_usernameBox.setSize(sf::Vector2f(300.0f, 50.0f));
    m_usernameBox.setFillColor(sf::Color::White);
    m_usernameBox.setPosition(width / 2 - 150.0f, height / 2 - 100.0f);

    m_passwordBox.setSize(sf::Vector2f(300.0f, 50.0f));
    m_passwordBox.setFillColor(sf::Color::White);
    m_passwordBox.setPosition(width / 2 - 150.0f, height / 2);

    m_usernameText.setFont(m_font);
    m_usernameText.setCharacterSize(25);
    m_usernameText.setString("Username:");
    m_usernameText.setPosition(width / 2 - 150.0f, height / 2 - 150.0f);

    m_passwordText.setFont(m_font);
    m_passwordText.setCharacterSize(25);
    m_passwordText.setString("Password:");
    m_passwordText.setPosition(width / 2 - 150.0f, height / 2 + 50.0f);

    m_username.setFont(m_font);
    m_username.setCharacterSize(25);
    m_username.setFillColor(sf::Color::Black);
    m_username.setPosition(m_usernameBox.getPosition().x + 5, m_usernameBox.getPosition().y + 10);

    m_password.setFont(m_font);
    m_password.setCharacterSize(25);
    m_password.setFillColor(sf::Color::Black);
    m_password.setPosition(m_passwordBox.getPosition().x + 5, m_passwordBox.getPosition().y + 10);
}

void LoginWindow::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_usernameBox);
    window.draw(m_passwordBox);
    window.draw(m_usernameText);
    window.draw(m_passwordText);
    window.draw(m_username);
    window.draw(m_password);
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
                m_isPasswordActive = false;
                m_usernameBox.setFillColor(sf::Color::Green);
                m_passwordBox.setFillColor(sf::Color::White);
            }
            else if (m_passwordBox.getGlobalBounds().contains(mousePos)) 
            {
                m_isUsernameActive = false;
                m_isPasswordActive = true;
                m_passwordBox.setFillColor(sf::Color::Green);
                m_usernameBox.setFillColor(sf::Color::White);
            }
            else
            {
                m_isUsernameActive = false;
                m_isPasswordActive = false;
                m_usernameBox.setFillColor(sf::Color::White);
                m_passwordBox.setFillColor(sf::Color::White);
            }
        }

        if (event.type == sf::Event::TextEntered) 
        {
            if (m_isUsernameActive)
            {
                handleTextInput(event, m_username);
            }
            else if (m_isPasswordActive) 
            {
                handlePasswordInput(event);
            }
        }
    }
}

bool LoginWindow::isLoginSuccessful() const 
{
    return !m_username.getString().isEmpty() && !m_passwordValue.empty();
}

void LoginWindow::handleTextInput(const sf::Event& event, sf::Text& target) {
    if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8) 
    {
        target.setString(target.getString() + static_cast<char>(event.text.unicode));
    }
    else if (event.text.unicode == 8 && target.getString().getSize() > 0)
    {
        std::string currentText = target.getString();
        currentText.pop_back();
        target.setString(currentText);
    }
}

void LoginWindow::handlePasswordInput(const sf::Event& event) 
{
    if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8) 
    {
        m_passwordValue += static_cast<char>(event.text.unicode);
        m_password.setString(std::string(m_passwordValue.size(), '*'));
    }
    else if (event.text.unicode == 8 && !m_passwordValue.empty())
    {
        m_passwordValue.pop_back();
        m_password.setString(std::string(m_passwordValue.size(), '*'));
    }
}
