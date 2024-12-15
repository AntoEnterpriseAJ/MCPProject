#include "LoginWindow.h"
#include <iostream>

LoginWindow::LoginWindow(float width, float height)
    : m_isUsernameActive{ false }, m_isLoginSuccessful{ false }
{
    if (!m_font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    if (!m_backgroundTexture.loadFromFile("res/textures/background_login.png"))
    {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    m_usernameBox.setSize(sf::Vector2f(300.0f, 70.0f));
    m_usernameBox.setFillColor(sf::Color::White);
    m_usernameBox.setPosition(width / 2 - 150.0f, height / 2 + 0.5f);

    m_username.setFont(m_font);
    m_username.setCharacterSize(34);
    m_username.setFillColor(sf::Color::Magenta);
    m_username.setPosition(m_usernameBox.getPosition().x + 5, m_usernameBox.getPosition().y + 10);

    m_usernameString = "";

    m_cursorClock.restart();
}

void LoginWindow::draw(sf::RenderWindow& window)
{
    window.draw(m_backgroundSprite);
    window.draw(m_username);

    if (m_isUsernameActive && m_showCursor)
    {
        float cursorX = m_username.findCharacterPos(m_cursorPosition).x;
        float cursorY = m_username.getPosition().y + 6.0f;

        sf::RectangleShape cursor(sf::Vector2f(2, m_username.getCharacterSize()));
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition(cursorX, cursorY);

        window.draw(cursor);
    }

    if (m_cursorClock.getElapsedTime().asSeconds() > 0.5f)
    {
        m_showCursor = !m_showCursor;
        m_cursorClock.restart();
    }
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

        if (event.type == sf::Event::KeyPressed && m_isUsernameActive)
        {
            if (event.key.code == sf::Keyboard::Left && m_cursorPosition > 0)
            {
                m_cursorPosition--;
            }
            else if (event.key.code == sf::Keyboard::Right && m_cursorPosition < m_usernameString.size())
            {
                m_cursorPosition++;
            }
        }
    }
}

void LoginWindow::handleTextInput(const sf::Event& event)
{
    if (event.text.unicode >= 32 && event.text.unicode < 128)
    {
        m_usernameString.insert(m_cursorPosition, 1, static_cast<char>(event.text.unicode));
        m_cursorPosition++;
    }
    else if (event.text.unicode == 8 && m_cursorPosition > 0)
    {
        m_usernameString.erase(m_cursorPosition - 1, 1);
        m_cursorPosition--;
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
