#pragma once

#include "PowerUp.h"
#include "Obstacle.h"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <cstdlib>

class PowerUpsManager
{
public:
    PowerUpsManager();
    void updatePowerUps();

private:
    void spawnRandomPowerUp();
    int  randomNumberGenerator(int lower, int higher);

private:
    static constexpr float kSpawnInterval = 3.0f;

private:
    std::vector<PowerUp> m_activePowerUps;
    sf::Clock            m_spawnTimer;
};
