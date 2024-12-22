#pragma once
#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	PowerUp(
		sf::Vector2f       pos,
		const sf::Texture& texture,
		sf::Vector2f       size,
		std::string        powerUpName
	);

private:
	std::string m_powerUpName;
};