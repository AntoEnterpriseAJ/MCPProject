#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    Button(const std::string& label, const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderWindow& window) const;
    bool isHovered(const sf::Vector2i& mousePosition) const;
    const sf::FloatRect getBounds() const;

private:
    sf::RectangleShape m_shape;
    sf::Text           m_text;
    sf::Font           m_font;
};
