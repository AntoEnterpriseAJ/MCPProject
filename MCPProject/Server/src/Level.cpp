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

void Level::load()
{
    auto random = [](int lowerBound, int upperBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, upperBound);
        return dist(gen);
        };

    std::array<int, kHeight* kWidth> map;
    GenerateGameMap(map.data());

    std::ranges::for_each(std::views::iota(0, static_cast<int>(kHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kWidth)), [&](int j) {
            int tex = map[i * kWidth + j];

            ObstacleType obstacleType{ tex };
            Vec2f position{ j * Obstacle::kObstacleSize, i * Obstacle::kObstacleSize };

            int bombBrickChance = random(1, 10);
            if (obstacleType == ObstacleType::Brick && bombBrickChance == 1) {
                obstacleType = ObstacleType::BombBrick;
            }

            auto obstacle = createObstacle(obstacleType, position);
            this->setObstacle({ i, j }, obstacle, obstacleType);
            });
        });
}

const Level::layoutTypes& Level::getLayoutTypes() const noexcept
{
    return m_layoutTypes;
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
        return {nullptr};
    }
    else if (obstacleType == ObstacleType::Brick)
    {
        return std::make_unique<Brick>(position);
    }
    else if (obstacleType == ObstacleType::BombBrick)
    {
        return std::make_unique<BombBrick>(position);
    }
    else if (obstacleType  == ObstacleType::Bush)
    {
        return std::make_unique<Bush>(position);
    }
    else if (obstacleType  == ObstacleType::UnbreakableBrick)
    {
        return std::make_unique<Brick>(position);
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