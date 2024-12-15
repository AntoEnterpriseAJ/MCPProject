#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class LoginWindow 
{
public:
    LoginWindow(float width, float height);

    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);

    bool isLoginSuccessful() const;

    std::string getUsername();

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_usernameText;
    sf::RectangleShape m_usernameBox;

    sf::Text m_username;
    std::string m_usernameString;

    bool m_isUsernameActive;
    bool m_isLoginSuccessful;

    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    size_t m_cursorPosition;
    sf::Clock m_cursorClock;
    bool m_showCursor;

    void handleTextInput(const sf::Event& event);
};