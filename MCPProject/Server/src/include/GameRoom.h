#pragma once
#include "Player.h"
#include "Level.h"
#include "Vec2f.h"
#include "BulletManager.h"
#include "PowerUpManager.h"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <chrono>

class GameRoom
{
public:
    GameRoom();
    GameRoom(uint8_t m_roomID);

    uint8_t addPlayer();
    nlohmann::json getStateResponse(uint32_t clientVersion) noexcept;
    void move(uint8_t playerID, Direction direction, float deltaTime);
    void shoot(uint8_t playerID);
    void update();

    const Level& getLevel() const noexcept;
    uint32_t getVersion() const noexcept;
    uint8_t getID() const noexcept;
    Player& getPlayer(uint8_t id);
    const std::unordered_map<uint8_t, Player>& getPlayers() const noexcept;
    std::unordered_map<uint8_t, Player>& getPlayers() noexcept;

public:
    static constexpr uint16_t kWindowWidth   { 1200 };
    static constexpr uint16_t kWindowHeight  { 800 };
    static constexpr uint16_t kMaxPlayers    { 4 };
    static constexpr uint16_t kPointsPerKill { 100 };
private:
    void updateBullets();
    void updatePlayerStates();
    void updatePlayersPowerUps();
    bool checkCollision(const Player& player, const Vec2f& newPosition);
private:
    static constexpr uint32_t kMaxVersion   { 1000000 };
    static constexpr std::array<Vec2f, 4> m_respawnPositions = {
        Vec2f{Player::kPlayerSizeX, Player::kPlayerSizeY},
        Vec2f{Level::kWidth * Level::kGridSize - Player::kPlayerSizeX, Player::kPlayerSizeY},
        Vec2f{Player::kPlayerSizeX, Level::kHeight * Level::kGridSize - Player::kPlayerSizeY},
        Vec2f{Level::kWidth * Level::kGridSize - Player::kPlayerSizeX, Level::kHeight * Level::kGridSize - Player::kPlayerSizeY}
    };
private:
    uint8_t  m_roomID;
    uint8_t  m_idCounter;
    uint32_t m_version;
    Level    m_level;
    BulletManager  m_bulletManager;
    PowerUpManager m_powerUpManager;
    std::unordered_map<uint8_t, Player> m_players;
    std::chrono::steady_clock::time_point m_lastUpdated;
};