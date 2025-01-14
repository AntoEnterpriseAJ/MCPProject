#include "TextBox.h"

TextBox::TextBox(
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Font& font,
    unsigned int fontSize
)
    : m_isFocused(false), m_inputText("")
{
    m_box.setSize(size);
    m_box.setPosition(position);
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineColor(sf::Color::Black);
    m_box.setOutlineThickness(2.0f);

    m_font = font;
    m_text.setFont(m_font);
    m_text.setCharacterSize(fontSize);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position.x + 5, position.y + 5);
}

void TextBox::setPosition(const sf::Vector2f& position)
{
    m_box.setPosition(position);
    m_text.setPosition(position.x + 5, position.y + 5);
}

void TextBox::setSize(const sf::Vector2f& size)
{
    m_box.setSize(size);
}

void TextBox::setFont(const sf::Font& font)
{
    m_font = font;
    m_text.setFont(font);
}

void TextBox::setFontSize(unsigned int fontSize)
{
    m_text.setCharacterSize(fontSize);
}

void TextBox::setFocus(bool focus)
{
    m_isFocused = focus;
    m_box.setOutlineColor(focus ? sf::Color::Blue : sf::Color::Black);
}

void TextBox::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void TextBox::setBoxColor(const sf::Color& color)
{
    m_box.setFillColor(color);
}

void TextBox::setOutlineColor(const sf::Color& color)
{
    m_box.setOutlineColor(color);
}

void TextBox::setOutlineThickness(float thickness)
{
    m_box.setOutlineThickness(thickness);
}

void TextBox::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        if (m_box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
            setFocus(true);
        }
        else
        {
            setFocus(false);
        }
    }

    if (!m_isFocused) return;

    if (event.type == sf::Event::TextEntered)
    {
        // Backspace
        if (event.text.unicode == 8)
        {
            if (!m_inputText.empty())
            {
                m_inputText.pop_back();
            }
        }
        // Valid ASCII characters
        else if (event.text.unicode < 128)
        {
            m_inputText += static_cast<char>(event.text.unicode);
        }

        m_text.setString(m_inputText);
    }
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(m_box);
    window.draw(m_text);
}

std::string TextBox::getText() const
{
    return m_inputText;
}
