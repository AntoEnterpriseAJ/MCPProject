#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class RegisterWindow
{
public:
    RegisterWindow(float width, float height);

    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);

    bool isRegisterSuccessful() const;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_usernameText;
    sf::Text m_passwordText;

    sf::RectangleShape m_usernameBox;
    sf::RectangleShape m_passwordBox;

    sf::String m_username;
    sf::String m_password;

    bool m_registerSuccessful = false;
};
