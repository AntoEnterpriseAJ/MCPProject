#pragma once
#include "GameObject.h"

class PowerUp : public GameObject
{
public:
	PowerUp(
		sf::Vector2f       pos,
		const sf::Texture& texture,
		std::string        powerUpName,
		sf::Vector2f       size = sf::Vector2f(kPowerUpSize, kPowerUpSize)
	);

private:
	static constexpr int kPowerUpSize = 20;

private:
	std::string m_powerUpName;
};