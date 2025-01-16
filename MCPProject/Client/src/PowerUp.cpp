#include "PowerUp.h"

PowerUp::PowerUp(
    const sf::Vector2f& position,
    const sf::Texture& texture,
    const sf::Vector2f& size,
    PowerUpEffect powerUpEffect
)
    : GameObject{ position, texture, size }, m_powerUpEffect{ powerUpEffect }
{}
