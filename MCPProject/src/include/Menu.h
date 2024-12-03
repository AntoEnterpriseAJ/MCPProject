#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);

    bool isStartGameSelected() const;
    bool isLoginSelected() const;
    bool isRegisterSelected() const;

private:
    sf::Font m_font;
    sf::Text m_startButton;
    sf::Text m_exitButton;
    sf::Text m_loginButton;
    sf::Text m_registerButton;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    bool m_startGameSelected = false;
    bool m_loginSelected = false;
    bool m_registerSelected = false;
};
