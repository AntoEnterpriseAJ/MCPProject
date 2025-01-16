#include "PowerUpManager.h"
#include <random>
#include <iostream>

PowerUpManager::PowerUpManager()
    : m_lastSpawn(std::chrono::steady_clock::now())
{}

void PowerUpManager::update(
    std::unordered_map<uint8_t, Player>& players,
    const Level::levelLayout& levelLayout
)
{
    tryToSpawnPowerUp(levelLayout);
    handlePlayerCollisions(players);
    removeCollectedPowerUps();

    std::cout << "Currently there are " << m_collectablePowerUps.size() << " powerUps spawned\n";
}

const std::vector<PickablePowerUp>& PowerUpManager::getCollectablePowerUps() const
{
    return m_collectablePowerUps;
}

void PowerUpManager::handlePlayerCollisions(std::unordered_map<uint8_t, Player>& players) {
    for (auto& player : players | std::views::values)
    {
        for (auto& powerUp : m_collectablePowerUps)
        {
            if (player.collides(powerUp))
            {
                powerUp.Collect();
                player.addPowerUp(
                    std::make_unique<PowerUp>(powerUp.GetEffect(), powerUp.GetDuration())
                );
            }
        }
    }
}

void PowerUpManager::tryToSpawnPowerUp(const Level::levelLayout& levelLayout)
{
    auto random = [](int lower, int higher) -> int
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(lower, higher);
        return dist(gen);
    };

    auto now = std::chrono::steady_clock::now();
    auto timeSinceLastSpawn = std::chrono::duration_cast<std::chrono::seconds>(now - m_lastSpawn).count();

    if (timeSinceLastSpawn >= kSpawnTime)
    {
        Vec2f position{
            random(0, Level::kWidth - 1) * Level::kGridSize + Level::kGridSize / 2,
            random(0, Level::kHeight - 1) * Level::kGridSize + Level::kGridSize / 2
        };

        PowerUpEffect effect{ random(0, static_cast<int>(PowerUpEffect::HealthUp)) };
        effect = PowerUpEffect::HealthUp; // TODO: REMOVE, FOR TESTING ONLY

        PickablePowerUp powerUp{ position, PickablePowerUp::kPowerUpSize, effect, 10.0f };
        if (checkValidPosition(levelLayout, powerUp))
        {
            m_collectablePowerUps.push_back(std::move(powerUp));
            m_lastSpawn = now;
        }
    }
}

bool PowerUpManager::checkValidPosition(
    const Level::levelLayout& levelObstacles,
    const PickablePowerUp& powerUp
)
{
    auto [topLeftX, topLeftY] = powerUp.getTopLeft().toGridCoords(Level::kGridSize);
    auto [bottomRightX, bottomRightY] = powerUp.getBottomRight().toGridCoords(Level::kGridSize);

    for (int x = topLeftX; x <= bottomRightX; ++x)
    {
        for (int y = topLeftY; y <= bottomRightY; ++y)
        {
            if (x < 0 || x >= Level::kWidth || y < 0 || y >= Level::kHeight)
            {
                return false;
            }

            if (levelObstacles[y * Level::kWidth + x] != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

void PowerUpManager::removeCollectedPowerUps()
{
    std::erase_if(m_collectablePowerUps, [](const PickablePowerUp& powerUp) {
        return powerUp.IsCollected();
    });
}
