#include "PowerUpManager.h"
#include "SFML/Graphics.hpp"
#include <cstdlib>
#include <iostream>

#include "Bush.h"
#include "Brick.h"
#include "BombBrick.h"
#include "UnbreakableBrick.h"

PowerUpManager::PowerUpManager()
{
    m_spawnClock.restart();
}

void PowerUpManager::Update(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles)
{
    if (m_spawnClock.getElapsedTime().asSeconds() >= 3.0f)
    {
        SpawnRandomPowerUp(levelObstacles);
        m_spawnClock.restart();
    }
}

void PowerUpManager::SpawnRandomPowerUp(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles)
{
    sf::Vector2f randomPos;

    do
    {
        int x = randomNumberGenerator(0, 30) * 40 + 10;
        int y = randomNumberGenerator(0, 20) * 40 + 10;
        randomPos = sf::Vector2f(x, y);
    } while (!IsPositionValid(randomPos, levelObstacles));

    sf::Texture texture;
    if (!texture.loadFromFile("res/textures/albedo.png"))
    {
        std::cout << "Failed to open powerUp texture!\n";
        return;
    }

    std::string powerUpName = "SpeedBoost";

    PowerUp newPowerUp(randomPos, texture, powerUpName);
    m_activePowerUps.push_back(newPowerUp);

    std::cout << "PowerUp added!\n";
}

int PowerUpManager::randomNumberGenerator(int lower, int higher)
{
    return rand() % (higher - lower + 1) + lower;
}

bool PowerUpManager::IsPositionValid(const sf::Vector2f& position, const std::vector<std::unique_ptr<Obstacle>>& levelObstacles)
{
    sf::FloatRect newPowerUpBounds(position, sf::Vector2f(20.f, 20.f));

    for (const auto& obstacle : levelObstacles)
    {
        sf::FloatRect obstacleBounds(obstacle->GetBounds());

        if (obstacleBounds.intersects(newPowerUpBounds) &&
            (dynamic_cast<Bush*>(obstacle.get()) ||
                dynamic_cast<Brick*>(obstacle.get()) ||
                dynamic_cast<UnbreakableBrick*>(obstacle.get()) ||
                dynamic_cast<BombBrick*>(obstacle.get())))
        {
            return false;
        }
    }

    return true;
}

void PowerUpManager::Draw(sf::RenderWindow& window) const
{
    for (const auto& powerUp : m_activePowerUps)
    {
        window.draw(powerUp);
    }
}
