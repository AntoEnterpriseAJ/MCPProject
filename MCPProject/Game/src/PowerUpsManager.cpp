#include "PowerUpsManager.h"
#include <random>

void PowerUpsManager::spawnRandomPowerUp()
{
    auto getRandomIndex = [](int lowerBound, int higherBound) -> int {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(lowerBound, higherBound);
        return dist(gen);
        };

    int x = getRandomIndex(0, 20);
    int y = getRandomIndex(0, 30);
}