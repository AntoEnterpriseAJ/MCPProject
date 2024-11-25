#include "Level.h"
#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <random>

void Level::load()
{
    auto getRandomIndex = []() -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 5);
        return dist(gen);
        };

    loadBackground();

    int randomIndex = getRandomIndex();
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
            if (textureType == 0)
            {
                m_levelLayout.push_back(std::monostate{});
            }
            else if (textureType == 1)
            {
                Brick brick{position, ResourceManager::getInstance().getTexture("brick"), true};
                m_levelLayout.push_back(brick);
            }
            else if (textureType == 2)
            {
                Bush bush{position, ResourceManager::getInstance().getTexture("bush")};
                m_levelLayout.push_back(bush);
            }
            else if (textureType == 3)
            {
                UnbreakableBrick unbreakableBrick{position, ResourceManager::getInstance().getTexture("unbreakableBrick")};
                m_levelLayout.push_back(unbreakableBrick);
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
