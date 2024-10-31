#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(sf::Vector2f pos, sf::Texture texture, sf::Vector2f size = sf::Vector2f(30, 30));

private:
	
};