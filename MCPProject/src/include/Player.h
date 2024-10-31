#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f vel);

	

	void movePlayer(sf::Event e);

private:

};