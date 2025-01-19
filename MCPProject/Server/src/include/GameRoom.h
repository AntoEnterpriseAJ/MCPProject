#pragma once
#include "Player.h"
#include "Level.h"
#include "Vec2f.h"
#include "BulletManager.h"
#include "PowerUpManager.h"
#include "GameRoomState.h"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <chrono>

class GameRoom
{
public:
    GameRoom();
    GameRoom(uint8_t m_roomID);

    uint8_t addPlayer(uint16_t databaseID);
    nlohmann::json getGameStateResponse(uint32_t clientVersion) noexcept;
    void move(uint8_t playerID, Direction direction, float deltaTime);
    void setState(GameRoomState state);
    void shoot(uint8_t playerID);
    void tryToStart();
    void checkWinCondition();
    void update();
    void setUpdatedScore(bool updatedScore);

    bool getUpdatedScore() const noexcept;
    GameRoomState getState() const noexcept;
    const Level& getLevel() const noexcept;
    uint32_t getVersion() const noexcept;
    uint8_t getID() const noexcept;
    Player& getPlayer(uint8_t id);
    const std::vector<uint8_t>& getEliminatedPlayers() const noexcept;
    const std::unordered_map<uint8_t, Player>& getPlayers() const noexcept;
    std::unordered_map<uint8_t, Player>& getPlayers() noexcept;

public:
    static constexpr uint16_t kWindowWidth   { 1200 };
    static constexpr uint16_t kWindowHeight  { 800 };
    static constexpr uint16_t kMaxPlayers    { 4 };
    static constexpr uint16_t kMinPlayers    { 2 };
    static constexpr uint16_t kPointsPerKill { 100 };
private:
    void updateBullets();
    void updatePlayerStates();
    void updatePlayersPowerUps();
    void updateEliminatedPlayers();
    bool checkCollision(const Player& player, const Vec2f& newPosition);
private:
    static constexpr uint16_t kWaitingTime { 10 };
    static constexpr uint32_t kMaxVersion  { 1000000 };
    static constexpr std::array<Vec2f, kMaxPlayers> m_respawnPositions {
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
    bool     m_waitingToStart;
    bool     m_updatedScore;
    GameRoomState  m_state;
    BulletManager  m_bulletManager;
    PowerUpManager m_powerUpManager;
    std::vector<uint8_t> m_eliminatedPlayers;
    std::unordered_map<uint8_t, Player> m_players;
    std::chrono::steady_clock::time_point m_deltaTime;
    std::chrono::steady_clock::time_point m_roomStartTimer;
};