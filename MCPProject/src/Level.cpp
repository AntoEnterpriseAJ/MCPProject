#include "Level.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>

void Level::loadResources()
{
    auto getRandomIndex = []() -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 5);
        int randomNumber = dist(gen);
        return randomNumber;
        };

    int randomIndex = getRandomIndex();

    std::string levelFileName = "level" + std::to_string(randomIndex) + ".txt";


    std::ifstream fin(levelFileName);

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
                Brick brick(
                    sf::Vector2f(j * Brick::getSize(), i * Brick::getSize()), 
                    m_brickTexture, 
                    true
                );

                m_levelLayout.push_back(brick);
            }
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& obj : m_levelLayout)
    {
        target.draw(obj);
    }
}

Brick& Level::findBrick(float posX, float posY)
{
    for (auto& brick : m_levelLayout)
    {
        if (brick.getPosition().x == posX && brick.getPosition().y == posY)
        {
            return brick;
        }
    }
}

std::vector<Brick>& Level::getBricks()
{
    return m_levelLayout;
}
