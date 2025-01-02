#include "PowerUpsManager.h"
#include <random>

#include "Level.h"

PowerUpsManager::PowerUpsManager()
{
}

void PowerUpsManager::spawnRandomPowerUp()
{
    sf::Vector2f powerUpPosition;
    sf::Texture  powerUpTexture;
    std::string  powerUpName;


    int powerUpLowerBound = 0;
    int powerUpUpperBound = 2;

    int powerUpRandomIndex = randomNumberGenerator(powerUpLowerBound, powerUpUpperBound);

    switch (powerUpRandomIndex)
    {
    case 0:  powerUpName = "Rampage";        break;
    case 1:  powerUpName = "God";            break;
    case 2:  powerUpName = "BulletSpreader"; break;
    default: powerUpName = "NoName";         break;
    }



    bool isValid = true;
    while (isValid)
    {
        isValid = false;
        int x = randomNumberGenerator(0, 30);
        int y = randomNumberGenerator(0, 20);
    }
}

int PowerUpsManager::randomNumberGenerator(int lower, int upper)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(lower, upper);
    return dist(gen);
}
