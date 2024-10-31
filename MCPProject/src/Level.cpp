#include <fstream>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "Level.h"

void Level::loadResources()
{
	std::ifstream fin("levels.txt");

	if (!fin)
	{
		std::cout << "ERROR : Cannot open the file!\n";
		return;
	}

	sf::Texture brickTexture;
	if (!brickTexture.loadFromFile("res/albedo.png"))
	{
		std::cerr << "ERROR : Failed to load the texture!\n";
		return;
	}

	for (int i = 0; i < m_levelHeight; ++i)
		for (int j = 0; j < m_levelWidth; ++j)
		{
			int textureType;
			fin >> textureType;

			Brick brick;

			brick.setPosition(sf::Vector2f(i * 30, j * 30));
			brick.setTexture(brickTexture);
			brick.setSize(sf::Vector2f(0.5f, 0.5f));
			brick.setVelocity(sf::Vector2f(0, 0));

			m_levelLayout.push_back(brick);
		}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& obj : m_levelLayout)
		target.draw(obj);
}
