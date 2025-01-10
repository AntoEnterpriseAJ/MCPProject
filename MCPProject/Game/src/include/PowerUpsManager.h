#pragma once

#include "PowerUp.h"
#include "Obstacle.h"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <cstdlib>

#include "Brick.h"
#include "UnbreakableBrick.h"
#include "Bush.h"
#include "BombBrick.h"

class PowerUpsManager
{
public:
    PowerUpsManager();
    void updatePowerUps(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);

private:
    void spawnRandomPowerUp(const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);
    int  randomNumberGenerator(int lower, int higher);
    bool isPositionValid(float x, float y, const sf::Vector2f& size, 
        const std::vector<std::unique_ptr<Obstacle>>& levelObstacles);

private:
    static constexpr float kSpawnInterval = 3.0f;

private:
    std::vector<PowerUp> m_activePowerUps;
    sf::Clock            m_spawnTimer;
};
