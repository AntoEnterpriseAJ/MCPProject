#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>

class LoginWindow
{
public:
    LoginWindow(float width, float height);

    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);

    bool isLoginSuccessful() const;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_usernameText;
    sf::Text m_passwordText;
    sf::RectangleShape m_usernameBox;
    sf::RectangleShape m_passwordBox;

    sf::Text m_username;
    sf::Text m_password;

    bool m_isUsernameActive;
    bool m_isPasswordActive;

    std::string m_passwordValue;

    void handleTextInput(const sf::Event& event, sf::Text& target);

    void handlePasswordInput(const sf::Event& event);
};
