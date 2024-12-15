#include "Level.h"
#include "Brick.h"
#include "Bush.h"
#include "BombBrick.h"
#include "ResourceManager.h"
#include "Obstacle.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ranges>

void Level::load()
{
    auto getRandomIndex = [](int lowerBound, int upperBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, upperBound);
        return dist(gen);
    };

    loadBackground();

    int lowerBound = 1;
    int upperBound = 5;

    int randomIndex = getRandomIndex(lowerBound, upperBound);
    std::string levelFileName = "res/levels/level" + std::to_string(randomIndex) + ".txt";

    std::ifstream fin(levelFileName);
    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    m_levelLayout.reserve(kLevelHeight * kLevelWidth);

    std::ranges::for_each(std::views::iota(0, static_cast<int>(kLevelHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kLevelWidth)), [&](int j) {
            int textureType;
            fin >> textureType;

            if (textureType == 0) return;

            sf::Vector2f position{j * Obstacle::kObstacleSize, i * Obstacle::kObstacleSize};
            if (textureType == 1)
            {
                int bombBrickChance = getRandomIndex(1, 10);
                if (bombBrickChance == 1)
                {
                    m_levelLayout.emplace_back(std::make_unique<BombBrick>(
                        position, ResourceManager::getInstance().getTexture("bombBrick")));
                }
                else
                {
                    m_levelLayout.emplace_back(std::make_unique<Brick>(
                        position, ResourceManager::getInstance().getTexture("brick"), 3, false, true));
                }
            }
            else if (textureType == 2)
            {
                m_levelLayout.emplace_back(std::make_unique<Bush>(
                    position, ResourceManager::getInstance().getTexture("bush")));
            }
            else if (textureType == 3)
            {
                m_levelLayout.emplace_back(std::make_unique<Brick>(
                    position, ResourceManager::getInstance().getTexture("unbreakableBrick"), 3, false, false));
            }
            else
            {
                std::cerr << "Error! Invalid texture!\n";
            }
        });
    });
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::ranges::for_each(m_levelLayout, [&target](const auto& obj){
        target.draw(*obj);
    });
}

void Level::drawBackground(sf::RenderWindow& window) const
{
    window.draw(m_background);
}

std::unique_ptr<Obstacle>& Level::operator[](const Position& position)
{
    auto [posX, posY] = position;
    return m_levelLayout[posY * kLevelWidth + posX];
}

const std::unique_ptr<Obstacle>& Level::operator[](const Position& position) const
{
    auto [posX, posY] = position;
    return m_levelLayout[posY * kLevelWidth + posX];
}

void Level::loadBackground()
{
    m_background.setTexture(ResourceManager::getInstance().getTexture("background"));
    m_background.setPosition(sf::Vector2{ 0.0f, 0.0f });
}

std::vector<std::unique_ptr<Obstacle>>& Level::getBricks()
{
    return m_levelLayout;
}

const std::vector<std::unique_ptr<Obstacle>>& Level::getBricks() const
{
    return m_levelLayout;
}