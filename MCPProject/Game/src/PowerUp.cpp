#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size, std::string powerUpName)
	: GameObject(pos, texture, size), m_powerUpName(powerUpName)
{
}
