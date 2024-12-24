#pragma once

#include "PowerUp.h"

#include <vector>

class PowerUpsManager
{
public:
	void spawnRandomPowerUp();

private:
	std::vector<std::string> possiblePowerUps;
	std::vector<PowerUp>     activePowerUps;
};