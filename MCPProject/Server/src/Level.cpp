#include "Level.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ranges>
#include <string>
#include <array>
#include "Brick.h"
#include "BombBrick.h"
#include "Bush.h"
#include "../../MapGenerator/MapGenerator.h"

Level::Level()
    : m_ID{ 0 }, m_levelLayout{}, m_layoutTypes{}
{
}

void Level::load()
{
    auto random = [](int lowerBound, int upperBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, upperBound);
        return dist(gen);
        };

    uint8_t firstLevel{ 1 };
    uint8_t lastLevel{ 5 };
    uint8_t randomLevel{ static_cast<uint8_t>(random(firstLevel, lastLevel)) };

    m_ID = randomLevel;
    std::string levelFileName{ "res/levels/level" + std::to_string(randomLevel) + ".txt" };

    std::ifstream fin(levelFileName);
    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    std::array<int, kHeight* kWidth> map;
    GenerateGameMap(map);

    uint16_t currentBrickCount{ 0 };
    std::ranges::for_each(std::views::iota(0, static_cast<int>(kHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kWidth)), [&](int j) {
            // int tex; fin >> tex;
            int tex = map[i * kWidth + j]; //for DLL testing

            ObstacleType obstacleType{ tex };
            Vec2f position{ j * Obstacle::kObstacleSize, i * Obstacle::kObstacleSize };

            if (currentBrickCount < kMaxBombs)
            {
                int bombBrickChance = random(1, 10);
                if (obstacleType == ObstacleType::Brick && bombBrickChance == 1)
                {
                    obstacleType = ObstacleType::BombBrick;
                    currentBrickCount++;
                }
            }

            auto obstacle = createObstacle(obstacleType, position);
            this->setObstacle({ i, j }, obstacle, obstacleType);
            });
        });
}

void Level::updateLayoutTypes()
{
    std::ranges::for_each(std::views::iota(0, static_cast<int>(kHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kWidth)), [&](int j) {
            uint16_t index = i * kWidth + j;
            auto& obstacle = m_levelLayout[index];
            if (!obstacle && m_layoutTypes[index])
            {
                m_layoutTypes[index] = static_cast<uint16_t>(ObstacleType::None);
            }
            });
        });
}

const Level::layoutTypes& Level::getLayoutTypes() const noexcept
{
    return m_layoutTypes;
}

Level::layoutTypes& Level::getLayoutTypes()
{
    return m_layoutTypes;
}

const Level::levelLayout& Level::getLayout() const noexcept
{
    return m_levelLayout;
}

Level::levelLayout& Level::getLayout()
{
    return m_levelLayout;
}

void Level::setObstacle(const Position& position, std::unique_ptr<Obstacle>& obstacle, ObstacleType obstacleType)
{
    auto [posY, posX] = position;
    size_t index = posY * kWidth + posX;

    m_levelLayout[index] = std::move(obstacle);

    if (m_levelLayout[index])
    {
        m_layoutTypes[index] = static_cast<uint16_t>(obstacleType);
    }
    else
    {
        m_layoutTypes[index] = static_cast<uint16_t>(ObstacleType::None);
    }
}

std::unique_ptr<Obstacle> Level::createObstacle(ObstacleType obstacleType, const Vec2f& position)
{
    if (obstacleType == ObstacleType::None)
    {
        return { nullptr };
    }
    else if (obstacleType == ObstacleType::Brick)
    {
        return std::make_unique<Brick>(position);
    }
    else if (obstacleType == ObstacleType::BombBrick)
    {
        return std::make_unique<BombBrick>(position);
    }
    else if (obstacleType == ObstacleType::Bush)
    {
        return std::make_unique<Bush>(position);
    }
    else if (obstacleType == ObstacleType::UnbreakableBrick)
    {
        return std::make_unique<Brick>(position, 3, false, false);
    }
    else
    {
        std::cerr << std::format("Error! Invalid obstacle type: {}\n", static_cast<int>(obstacleType));
    }
}

std::unique_ptr<Obstacle>& Level::operator[](const Position& position)
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}

const std::unique_ptr<Obstacle>& Level::operator[](const Position& position) const
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}