#include "Level.h"
#include "Brick.h"
#include "UnbreakableBrick.h"
#include "Bush.h"
#include "BombBrick.h"
#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <random>

void Level::load()
{
    auto getRandomIndex = [](int lowerBound, int higherBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, higherBound);
        return dist(gen);
        };

    loadBackground();

    int lowerBound = 1;
    int higherBound = 5;

    int randomIndex = getRandomIndex(lowerBound, higherBound);
    std::string levelFileName = "res/levels/level" + std::to_string(randomIndex) + ".txt";

    std::ifstream fin(levelFileName);
    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    m_levelLayout.reserve(kLevelHeight * kLevelWidth);

    for (int i = 0; i < kLevelHeight; ++i)
    {
        for (int j = 0; j < kLevelWidth; ++j)
        {
            int textureType;
            fin >> textureType;

            sf::Vector2f position(j * Brick::getSize(), i * Brick::getSize());

            switch (textureType)
            {
                case 0:
                    m_levelLayout.emplace_back(nullptr); // Empty space
                    break;
                case 1:
                {
                    int bombBrickChance = getRandomIndex(1, 10);
                    if (bombBrickChance == 1)
                    {
                        m_levelLayout.emplace_back(std::make_unique<BombBrick>(
                            position, ResourceManager::getInstance().getTexture("bombBrick"), true));
                    }
                    else
                    {
                        m_levelLayout.emplace_back(std::make_unique<Brick>(
                            position, ResourceManager::getInstance().getTexture("brick"), true));
                    }
                    break;
                }
                case 2:
                    m_levelLayout.emplace_back(std::make_unique<Bush>(
                        position, ResourceManager::getInstance().getTexture("bush")));
                    break;
                case 3:
                    m_levelLayout.emplace_back(std::make_unique<UnbreakableBrick>(
                        position, ResourceManager::getInstance().getTexture("unbreakableBrick")));
                    break;
                default:
                    std::cerr << "Error! Invalid texture!\n";
                    break;
            }
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& obj : m_levelLayout)
    {
        if (obj)
        {
            obj->draw(target, states);
        }
    }
}

void Level::drawBackground(sf::RenderWindow& window) const
{
    window.draw(m_background);
}

void Level::loadBackground()
{
    m_background.setTexture(ResourceManager::getInstance().getTexture("background"));
    m_background.setPosition(sf::Vector2{ 0.0f, 0.0f });
}

std::vector<std::unique_ptr<GameObject>>& Level::getBricks()
{
    return m_levelLayout;
}

const std::vector<std::unique_ptr<GameObject>>& Level::getBricks() const
{
    return m_levelLayout;
}