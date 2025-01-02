#include "PowerUp.h"


PowerUp::PowerUp(sf::Vector2f pos, const sf::Texture& texture, std::string powerUpName, sf::Vector2f size)
	: GameObject(pos, texture, size), m_powerUpName(powerUpName)
{
}
