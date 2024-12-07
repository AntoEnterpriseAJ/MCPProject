#include "RegisterWindow.h"
#include <iostream>

RegisterWindow::RegisterWindow(float width, float height)
{
    if (!m_font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    m_title.setFont(m_font);
    m_title.setCharacterSize(50);
    m_title.setString("Register");
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
}

void RegisterWindow::draw(sf::RenderWindow& window)
{
    window.draw(m_title);
    window.draw(m_usernameBox);
    window.draw(m_passwordBox);
    window.draw(m_usernameText);
    window.draw(m_passwordText);

    sf::Text username(m_username, m_font, 25);
    username.setPosition(m_usernameBox.getPosition().x + 5, m_usernameBox.getPosition().y + 10);
    window.draw(username);

    sf::Text password(m_password, m_font, 25);
    password.setPosition(m_passwordBox.getPosition().x + 5, m_passwordBox.getPosition().y + 10);
    window.draw(password);
}

void RegisterWindow::handleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::TextEntered)
        {
            if (m_usernameBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8)
                {
                    m_username += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == 8 && !m_username.isEmpty())
                {
                    m_username.erase(m_username.getSize() - 1, 1);
                }
            }
            else if (m_passwordBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8)
                {
                    m_password += '*';
                }
                else if (event.text.unicode == 8 && !m_password.isEmpty())
                {
                    m_password.erase(m_password.getSize() - 1, 1);
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (m_usernameBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                m_passwordBox.setFillColor(sf::Color::White);
                m_usernameBox.setFillColor(sf::Color::Green);
            }
            else if (m_passwordBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                m_usernameBox.setFillColor(sf::Color::White);
                m_passwordBox.setFillColor(sf::Color::Green);
            }
        }
    }
}

bool RegisterWindow::isRegisterSuccessful() const
{
    return m_registerSuccessful;
}
