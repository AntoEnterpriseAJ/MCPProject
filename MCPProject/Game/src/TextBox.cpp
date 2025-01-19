#include "TextBox.h"

TextBox::TextBox()
{
}

TextBox::TextBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, unsigned int characterSize)
    : m_isSelected(false)
    , m_cursorBlinkTime(0)
    , m_showCursor(true)
{
    m_background.setSize(size);
    m_background.setPosition(position);
    m_background.setFillColor(sf::Color::White);
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position.x + 5, position.y + (size.y - characterSize) / 2.0f);

    m_cursor.setSize(sf::Vector2f(2, characterSize));
    m_cursor.setFillColor(sf::Color::Black);
    updateCursorPosition();
}

void TextBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect bounds = m_background.getGlobalBounds();
        setSelected(bounds.contains(mousePos.x, mousePos.y));
    }
    else if (event.type == sf::Event::TextEntered && m_isSelected)
    {
        if (event.text.unicode == '\b')  // Backspace
        {
            std::string str = m_text.getString();
            if (!str.empty())
            {
                str.pop_back();
                m_text.setString(str);
            }
        }
        else if (event.text.unicode < 128)
        {
            m_text.setString(m_text.getString() + static_cast<char>(event.text.unicode));
        }
        updateCursorPosition();
    }

    m_cursorBlinkTime += 0.1f;
    if (m_cursorBlinkTime >= 0.5f)
    {
        m_cursorBlinkTime = 0;
        m_showCursor = !m_showCursor;
    }
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_text);
    if (m_isSelected && m_showCursor)
    {
        window.draw(m_cursor);
    }
}

void TextBox::setSelected(bool selected)
{
    m_isSelected = selected;
    m_background.setOutlineColor(selected ? sf::Color::Blue : sf::Color::Black);
}

bool TextBox::isSelected() const
{
    return m_isSelected;
}

std::string TextBox::getText() const
{
    return m_text.getString();
}

void TextBox::setText(const std::string& text)
{
    m_text.setString(text);
    updateCursorPosition();
}

void TextBox::setPosition(const sf::Vector2f& position)
{
    m_background.setPosition(position);
    m_text.setPosition(position.x + 5, position.y + (m_background.getSize().y - m_text.getCharacterSize()) / 2.0f);
    updateCursorPosition();
}

void TextBox::setSize(const sf::Vector2f& size)
{
    m_background.setSize(size);
    updateCursorPosition();
}

void TextBox::updateCursorPosition()
{
    sf::Vector2f textPos = m_text.getPosition();
    m_cursor.setPosition(
        textPos.x + m_text.getGlobalBounds().width + 2,
        textPos.y
    );
}