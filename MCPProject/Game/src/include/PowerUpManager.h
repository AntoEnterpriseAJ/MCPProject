#pragma once
#include "PowerUp.h"
#include "Obstacle.h"
#include <vector>
#include <SFML/System/Clock.hpp>

class PowerUpManager
{
public:
    PowerUpManager();

    void Update(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);
    void Draw(sf::RenderWindow& window) const;
    void SpawnRandomPowerUp(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);

private:
    std::vector<PowerUp> m_collectablePowerUps;
    sf::Clock m_spawnClock;

    int randomNumberGenerator(int lower, int higher);
    bool IsPositionValid(const sf::Vector2f& position, const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);
};
