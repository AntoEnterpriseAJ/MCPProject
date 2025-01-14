#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
public:
    TextBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, unsigned int fontSize);

    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    void setFont(const sf::Font& font);
    void setFontSize(unsigned int fontSize);
    void setFocus(bool focus);
    void setTextColor(const sf::Color& color);
    void setBoxColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
    std::string getText() const;

private:
    sf::RectangleShape m_box;
    sf::Text m_text;
    sf::Font m_font;
    bool m_isFocused;
    std::string m_inputText;
};