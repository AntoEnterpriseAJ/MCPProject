#pragma once
#include "PickablePowerUp.h"
#include "Obstacle.h"
#include "Level.h"
#include "Player.h"
#include <vector>
#include <chrono>

class PowerUpManager
{
public:
    PowerUpManager();

    void update(std::unordered_map<uint8_t, Player>& players, const Level::levelLayout& levelLayout);

    const std::vector<PickablePowerUp>& getCollectablePowerUps() const;

private:
    bool checkValidPosition(
        const Level::levelLayout& levelObstacles,
        const PickablePowerUp& powerUp
    );
    void tryToSpawnPowerUp(const Level::levelLayout& levelLayout);
    void handlePlayerCollisions(std::unordered_map<uint8_t, Player>& players);
    void removeCollectedPowerUps();
private:
    static constexpr float kSpawnTime{ 10.0f };
private:
    std::vector<PickablePowerUp> m_collectablePowerUps;
    std::chrono::steady_clock::time_point m_lastSpawn;
};
