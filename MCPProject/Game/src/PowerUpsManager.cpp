#include "PowerUpsManager.h"

#include <iostream> // Debug purpose
 
PowerUpsManager::PowerUpsManager()
{
    m_spawnTimer.restart();
}

void PowerUpsManager::updatePowerUps()
{
    if (m_spawnTimer.getElapsedTime().asSeconds() >= kSpawnInterval)
    {
        spawnRandomPowerUp();
        m_spawnTimer.restart();
    }
}

void PowerUpsManager::spawnRandomPowerUp()
{
    sf::Vector2f randomPosition(
        static_cast<float>(randomNumberGenerator(0, 800)),
        static_cast<float>(randomNumberGenerator(0, 600))
    );

    sf::Texture texture;
    if (!texture.loadFromFile("res/textures/albedo.png")) {
        std::cout << "POWERUP TEXTURE DON T LOAD!" << std::endl;
        return;
    }
    

    std::vector<std::string> powerUpNames = { "SpeedBoost", "Damage", "DoublePoints" };
    std::string randomName = powerUpNames[randomNumberGenerator(0, powerUpNames.size() - 1)];

    PowerUp newPowerUp(randomPosition, texture, randomName);
    m_activePowerUps.push_back(newPowerUp);

    std::cout << "PowerUp spawned!" << std::endl;
    std::cout << "  Position : " << randomPosition.x << " " << randomPosition.y << std::endl;
    std::cout << "  Name : " << randomName << std::endl;
}

int PowerUpsManager::randomNumberGenerator(int lower, int higher)
{
    return lower + (std::rand() % (higher - lower + 1));
}
