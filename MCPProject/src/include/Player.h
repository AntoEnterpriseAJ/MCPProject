#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(sf::RectangleShape rect);

	sf::RectangleShape getPlayerShape();

	void movePlayer(sf::Event e);

private:
	sf::RectangleShape m_rectangle;
};