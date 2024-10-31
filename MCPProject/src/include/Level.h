#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <variant>

#include "Brick.h"
#include "GameObject.h"

class Level : public GameObject
{
public:
	void loadResources();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	int m_levelWidth  = 30;
	int m_levelHeight = 20;
	std::vector<GameObject> m_levelLayout;
};