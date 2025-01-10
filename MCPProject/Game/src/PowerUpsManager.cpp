#include "PowerUpsManager.h"

#include <iostream> // Debug purpose
 
PowerUpsManager::PowerUpsManager()
{
    m_spawnTimer.restart();
}

void PowerUpsManager::updatePowerUps(const std::vector<std::unique_ptr<Obstacle>>& levelOstacles)
{
    if (m_spawnTimer.getElapsedTime().asSeconds() >= kSpawnInterval)
    {
        spawnRandomPowerUp(levelOstacles);
        m_spawnTimer.restart();
    }
}

bool PowerUpsManager::isPositionValid(float x, float y, const sf::Vector2f& size, 
    const std::vector<std::unique_ptr<Obstacle>>& levelObstacles)
{
    sf::Vector2f position{ x * 40, y * 40 };

    if (position.x < 0 || position.y < 0 || position.x + size.x > 1200 || position.y + size.y > 800)
    {
        return false;
    }

    for (const auto& powerUp : m_activePowerUps)
    {
        sf::FloatRect powerUpBounds(powerUp.GetPosition(), powerUp.GetSize());
        sf::FloatRect newPowerUpBounds(position, size);

        if (powerUpBounds.intersects(newPowerUpBounds))
        {
            return false;
        }
    }
    
    for (const auto& obstacle : levelObstacles)
    {
        if (dynamic_cast<Brick*>(obstacle.get()) ||
            dynamic_cast<Bush*>(obstacle.get()) ||
            dynamic_cast<UnbreakableBrick*>(obstacle.get()) ||
            dynamic_cast<BombBrick*>(obstacle.get()))
        {
            sf::FloatRect obstacleBounds(obstacle->GetPosition(), obstacle->GetSize());
            sf::FloatRect newPowerUpBounds(position, size);

            if (obstacleBounds.intersects(newPowerUpBounds))
            {
                return false;
            }
        }
    }

    return true;
}

void PowerUpsManager::spawnRandomPowerUp(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles)
{
    sf::Texture texture;
    if (!texture.loadFromFile("powerup.png"))
    {
        std::cerr << "Error: Failed to load texture: powerup.png" << std::endl;
        return;
    }

    sf::Vector2f size(20.f, 20.f);
    sf::Vector2f position;

    do
    {
        position = sf::Vector2f(static_cast<float>(randomNumberGenerator(0, 30)),
            static_cast<float>(randomNumberGenerator(0, 20)));
    } while (!isPositionValid(position.x * 40, position.y * 40, size, levelObstacles));

    std::vector<std::string> powerUpNames = { "SpeedBoost", "Damage", "DoublePoints" };
    std::string randomName = powerUpNames[randomNumberGenerator(0, powerUpNames.size() - 1)];

    PowerUp newPowerUp(position, texture, randomName);
    m_activePowerUps.push_back(newPowerUp);
}


int PowerUpsManager::randomNumberGenerator(int lower, int higher)
{
    return lower + (std::rand() % (higher - lower + 1));
}
