#include "Level.h"
#include <fstream>
#include <iostream>
#include <random>
#include <ranges>
#include <string>

void Level::load()
{
    auto random = [](int lowerBound, int upperBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, upperBound);
        return dist(gen);
    };

    uint8_t firstLevel  {1};
    uint8_t lastLevel   {5};
    uint8_t randomLevel {static_cast<uint8_t>(random(firstLevel, lastLevel))};

    m_ID = randomLevel;
    std::string levelFileName{"res/levels/level" + std::to_string(randomLevel) + ".txt"};

    std::ifstream fin(levelFileName);
    if (!fin)
    {
        std::cerr << "ERROR: Cannot open the file!\n";
        return;
    }

    std::ranges::for_each(std::views::iota(0, static_cast<int>(kHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kWidth)), [&](int j) {
            fin >> (*this)[{i, j}];

            //TODO: fix the magic numbers when the LevelGenerator is implemented
            if ((*this)[{i, j}] == 1)
            {
                int bombBrickChance = random(1, 10);
                if (bombBrickChance == 4)
                {
                    (*this)[{i, j}] = 4;
                }
            }
        });
    });
}

const Level::levelLayout& Level::getLayout() const noexcept
{
    return m_levelLayout;
}

uint16_t& Level::operator[](const Position& position)
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}

const uint16_t& Level::operator[](const Position& position) const
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}
