export module TextBox;


import <SFML/Graphics.hpp>;
import <string>;

export class TextBox {
public:
    TextBox();

    TextBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, unsigned int characterSize);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    void setSelected(bool selected);
    bool isSelected() const;

    std::string getText() const;
    void setText(const std::string& text);

    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);

private:
    sf::RectangleShape m_background;
    sf::Text m_text;
    sf::RectangleShape m_cursor;
    bool m_isSelected;
    float m_cursorBlinkTime;
    bool m_showCursor;

    void updateCursorPosition();
};