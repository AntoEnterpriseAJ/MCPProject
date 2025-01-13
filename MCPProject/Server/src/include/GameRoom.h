#pragma once
#include "Player.h"
#include "Level.h"
#include "Vec2f.h"
#include "BulletManager.h"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <chrono>

class GameRoom
{
public:
    GameRoom();
    GameRoom(uint8_t m_roomID);

    uint8_t addPlayer(const Vec2f& position);
    nlohmann::json getStateResponse(uint32_t clientVersion) noexcept;
    void move(uint8_t playerID, Direction direction, float deltaTime);
    void shoot(uint8_t playerID);
    void update();

    const Level& getLevel() const noexcept;
    uint32_t getVersion() const noexcept;
    uint8_t getID() const noexcept;
    Player& getPlayer(uint8_t id);
    const std::unordered_map<uint8_t, Player>& getPlayers() const noexcept;

public:
    static constexpr uint16_t kWindowWidth  { 1200 };
    static constexpr uint16_t kWindowHeight { 800 };
private:
    bool checkCollision(const Player& player, const Vec2f& newPosition);
private:
    static constexpr uint32_t kMaxVersion   { 1000000 };
private:
    uint8_t  m_roomID;
    uint8_t  m_idCounter;
    uint32_t m_version;
    Level    m_level;
    BulletManager m_bulletManager;
    std::unordered_map<uint8_t, Player> m_players;
    std::chrono::steady_clock::time_point m_lastUpdated;
};