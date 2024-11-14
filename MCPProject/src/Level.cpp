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
        return dist(gen);
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
        std::cerr << "ERROR: Failed to load the brick texture!\n";
        return;
    }

    if (!m_bushTexture.loadFromFile("res/bush.png"))
    {
        std::cerr << "ERROR: Failed to load the bush texture!\n";
        return;
    }

    for (int i = 0; i < m_levelHeight; ++i)
    {
        for (int j = 0; j < m_levelWidth; ++j)
        {
            int textureType;
            fin >> textureType;

            sf::Vector2f position(j * Brick::getSize(), i * Brick::getSize());
            if (textureType == 1)
            {
                Brick brick(position, m_brickTexture, true);
                m_levelLayout.push_back(brick);
            }
            else if (textureType == 2)
            {
                Bush bush(position, m_bushTexture);
                m_levelLayout.push_back(bush);
            }
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& obj : m_levelLayout)
    {
        std::visit([&target, &states](const auto& obj) { target.draw(obj, states); }, obj);
    }
}

Brick& Level::findBrick(float posX, float posY)
{

    for (auto& obj : m_levelLayout)
    {
        if (auto* brick = std::get_if<Brick>(&obj))
        {
            if (std::abs(brick->getPosition().x - posX) == 0 &&
                std::abs(brick->getPosition().y - posY) == 0)
            {
                return *brick;
            }
        }
    }
}

std::vector<std::variant<Brick, Bush>>& Level::getBricks()
{
    return m_levelLayout;
}