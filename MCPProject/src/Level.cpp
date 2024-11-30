#include "Level.h"
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
    int higherBound = 10;

    int randomIndex = getRandomIndex(lowerBound, higherBound);
    std::string levelFileName = "res/levels/level" + std::to_string(randomIndex) + ".txt";

    std::ifstream fin(levelFileName);
    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    m_levelLayout.reserve(kLevelHeight * kLevelWidth);

    // TODO std::emplace_back not explicit enough, maybe std::push_back(std::move());
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
                {
                    m_levelLayout.emplace_back(std::monostate{});
                    break;
                }
                case 1:
                {
                    int bombBrickChange = getRandomIndex(1, 10);

                    if (bombBrickChange == 1)
                    {
                        m_levelLayout.emplace_back(
                            BombBrick{ position, ResourceManager::getInstance().getTexture("bombBrick"), true });
                    }
                    else
                    {
                        m_levelLayout.emplace_back(
                            Brick{ position, ResourceManager::getInstance().getTexture("brick"), true });
                    }

                    break;
                }
                case 2:
                {
                    m_levelLayout.emplace_back(
                        Bush{ position, ResourceManager::getInstance().getTexture("bush") });
                    break;
                }
                case 3:
                {
                    m_levelLayout.emplace_back(
                        UnbreakableBrick{ position, ResourceManager::getInstance().getTexture("unbreakableBrick") });
                    break;
                }
                default:
                {
                    std::cerr << "Error! Invalid texture!\n";
                    break;
                }
            }
        }
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& obj : m_levelLayout)
    {
        std::visit([&target, &states](const auto& levelObject)
        {
            using objType = std::decay_t<decltype(levelObject)>;

            if constexpr (!std::is_same_v<objType, std::monostate>)
            {
                levelObject.draw(target, states);
            }

        }, obj);
    }
}

void Level::drawBackground(sf::RenderWindow& window) const
{
    window.draw(m_background);
}

LevelObject& Level::operator[](const Position& position)
{
    const auto& [row, column] = position;
    return m_levelLayout[row * kLevelWidth + column];
}

const LevelObject& Level::operator[](const Position& position) const
{
    const auto& [row, column] = position;
    return m_levelLayout[row * kLevelHeight + column];
}

std::vector<LevelObject>& Level::getBricks()
{
    return m_levelLayout;
}

const std::vector<LevelObject>& Level::getBricks() const
{
    return m_levelLayout;
}

void Level::loadBackground()
{
    m_background.setTexture(ResourceManager::getInstance().getTexture("background"));
    m_background.setPosition(sf::Vector2{ 0.0f, 0.0f });
}
