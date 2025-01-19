module Button;

Button::Button(
    const std::string& label,
    const sf::Vector2f& position,
    const sf::Vector2f& size
)
{

    if (!m_font.loadFromFile("res/font_text/static/Jaro_9pt-Regular.ttf"))
    {
        throw std::runtime_error("Failed to load font!");
    }

    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(3.f);

    m_text.setFont(m_font);
    m_text.setString(label);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    m_text.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
    window.draw(m_text);
}

bool Button::isHovered(const sf::Vector2i& mousePosition) const
{
    return m_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

const sf::FloatRect Button::getBounds() const
{
    return m_shape.getGlobalBounds();
}
