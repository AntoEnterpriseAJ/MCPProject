#pragma once

#include "PowerUp.h"
#include "Obstacle.h"

#include <vector>

class PowerUpsManager
{
public:
	PowerUpsManager();

	void spawnRandomPowerUp();

private:
	int randomNumberGenerator(int lower, int higher);

private:
	std::vector<PowerUp> m_activePowerUps;
};