#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!backgroundTexture.loadFromFile("res/textures/background_menu.png"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(width) / backgroundTexture.getSize().x,
        static_cast<float>(height) / backgroundTexture.getSize().y
    );

    if (!m_font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    m_startButton.setFont(m_font);
    m_startButton.setCharacterSize(50);
    m_startButton.setString("Start Game");
    m_startButton.setPosition(width / 2 - m_startButton.getLocalBounds().width / 2, height / 2 - 150);

    m_exitButton.setFont(m_font);
    m_exitButton.setCharacterSize(50);
    m_exitButton.setString("Exit");
    m_exitButton.setPosition(width / 2 - m_exitButton.getLocalBounds().width / 2, height / 2 + 150);

    m_loginButton.setFont(m_font);
    m_loginButton.setCharacterSize(50);
    m_loginButton.setString("Login");
    m_loginButton.setPosition(width / 2 - m_loginButton.getLocalBounds().width / 2, height / 2 - 50);

    m_registerButton.setFont(m_font);
    m_registerButton.setCharacterSize(50);
    m_registerButton.setString("Register");
    m_registerButton.setPosition(width / 2 - m_registerButton.getLocalBounds().width / 2, height / 2 + 50);
}

void Menu::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(m_startButton);
    window.draw(m_exitButton);
    window.draw(m_loginButton);
    window.draw(m_registerButton);
}

void Menu::handleInput(sf::RenderWindow& window)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (m_startButton.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_startGameSelected = true;
    }

    if (m_exitButton.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window.close();
    }

    if (m_loginButton.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_loginSelected = true;
    }

    if (m_registerButton.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_registerSelected = true;
    }
}

bool Menu::isStartGameSelected() const
{
    return m_startGameSelected;
}

bool Menu::isLoginSelected() const
{
    return m_loginSelected;
}

bool Menu::isRegisterSelected() const
{
    return m_registerSelected;
}