#include <fstream>
#include <iostream>
#include "Level.h"

void Level::loadResources()
{
    std::ifstream fin("levels.txt");

    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    if (!m_brickTexture.loadFromFile("res/albedo.png"))
    {
        std::cerr << "ERROR: Failed to load the texture!\n";
        return;
    }

    for (int i = 0; i < m_levelHeight; ++i)
    {
        for (int j = 0; j < m_levelWidth; ++j)
        {
            int textureType;
            fin >> textureType;

            if (textureType == 1)
            {
                Brick brick(sf::Vector2f(j * Brick::getSize(), i * Brick::getSize()), m_brickTexture);
                m_levelLayout.push_back(brick);
            }
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& obj : m_levelLayout)
    {
        target.draw(obj); // draw bricks
    }
}

std::vector<Brick>& Level::getBricks()
{
    return m_levelLayout;
}

const std::vector<Brick>& Level::getBricks() const
{
    return m_levelLayout;
}
