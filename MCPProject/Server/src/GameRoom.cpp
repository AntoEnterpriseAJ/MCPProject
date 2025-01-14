#include "GameRoom.h"
#include "ObstacleType.h"

#include <iostream>

GameRoom::GameRoom()
    : m_idCounter{ 0 }, m_roomID{ 0 }, m_version{ 1 }, m_players{}
{}

GameRoom::GameRoom(uint8_t m_roomID)
    : m_roomID{ m_roomID }, m_idCounter{ 0 }, m_version{ 0 }, m_players{}, m_level{}
{
    m_level.load();
}

uint8_t GameRoom::addPlayer()
{
    m_players.emplace(m_idCounter, m_respawnPositions[m_idCounter]);
    m_players.at(m_idCounter).setRespawnPosition(m_respawnPositions[m_idCounter]);

    m_version = (m_version + 1) % kMaxVersion;
    return m_idCounter++;
}

nlohmann::json GameRoom::getStateResponse(uint32_t clientVersion) noexcept
{
    nlohmann::json response = {
        {"serverVersion", m_version},
    };

    if (clientVersion != m_version)
    {
        m_level.updateLayoutTypes();
        response["levelLayout"] = m_level.getLayoutTypes();

        response["players"] = nlohmann::json::array();
        for (const auto& [id, player] : m_players)
        {
            response["players"].push_back({
                {"id", id},
                {"position", {player.GetPosition().x, player.GetPosition().y}}, // TODO: custom serialization
                {"direction", player.GetDirection()},
                {"lives", player.GetLives()},
                {"health", player.GetHealth()},
                {"state", player.GetState()},
                {"points", player.GetPoints()},
                });
        }

        update();
        response["bullets"] = nlohmann::json::array();
        for (const auto& bullet : m_bulletManager.getBullets())
        {
            response["bullets"].push_back({
                {"position", {bullet->GetPosition().x, bullet->GetPosition().y}},
                {"direction", bullet->getDirection()},
                });
        }
    }

    return response;
}

void GameRoom::move(uint8_t playerID, Direction direction, float deltaTime)
{
    auto alignToGrid = [](float value, int gridSize) -> float {
        return std::round(value / gridSize) * gridSize;
        };

    Player& player{ m_players.at(playerID) };
    Vec2f newPosition{ player.GetPosition() };

    if (direction != player.GetDirection())
    {
        if (direction == Direction::Up || direction == Direction::Down)
        {
            newPosition.x = alignToGrid(newPosition.x, Level::kGridSize / 2.0f);
        }
        else if (direction == Direction::Left || direction == Direction::Right)
        {
            newPosition.y = alignToGrid(newPosition.y, Level::kGridSize / 2.0f);
        }
    }

    player.setDirection(direction);
    if (direction == Direction::Up)
    {
        newPosition.y -= Player::kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Down)
    {
        newPosition.y += Player::kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Left)
    {
        newPosition.x -= Player::kPlayerSpeed * deltaTime;
    }
    else if (direction == Direction::Right)
    {
        newPosition.x += Player::kPlayerSpeed * deltaTime;
    }

    if (!checkCollision(player, newPosition))
    {
        player.setPosition(newPosition);
    }

    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::shoot(uint8_t playerID)
{
    Player& player{ m_players.at(playerID) };

    if (!player.canShoot()) return;

    player.resetShootCooldown();
    Vec2f offset{ 0.0f, 0.0f };
    Bullet bullet{ {0.0f, 0.0f}, Direction::Up };

    switch (player.GetDirection())
    {
    case Direction::Up:
        offset = { 0.0f, -Player::kPlayerSizeY - bullet.GetSize().y / 2.0f };
        break;
    case Direction::Down:
        offset = { 0.0f, Player::kPlayerSizeY + bullet.GetSize().y / 2.0f };
        break;
    case Direction::Left:
        offset = { -Player::kPlayerSizeX - bullet.GetSize().x / 2.0f, 0.0f};
        break;
    case Direction::Right:
        offset = { Player::kPlayerSizeX + bullet.GetSize().x / 2.0f, 0.0f};
        break;
    }

    m_bulletManager.addBullet(std::make_unique<Bullet>(player.GetPosition() + offset, player.GetDirection()));
    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::update()
{
    updateBullets();
    updatePlayerStates();
}

void GameRoom::updatePlayerStates()
{
    bool updated = false;
    for (auto& [id, player] : m_players | std::views::filter([](const auto& pair) { return !pair.second.isAlive() && pair.second.canRespawn(); }))
    {
        player.respawn();
        player.setPosition(m_respawnPositions[id]);
        updated = true;
    }

    if (updated)
    {
        m_version = (m_version + 1) % kMaxVersion;
    }
}

void GameRoom::updateBullets()
{
    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - m_lastUpdated).count();
    m_lastUpdated = now;
    m_bulletManager.update(m_level, m_players, deltaTime);

    m_version = (m_version + 1) % kMaxVersion;
}

const Level& GameRoom::getLevel() const noexcept
{
    return m_level;
}

uint32_t GameRoom::getVersion() const noexcept
{
    return m_version;
}

uint8_t GameRoom::getID() const noexcept
{
    return m_roomID;
}

Player& GameRoom::getPlayer(uint8_t id)
{
    return m_players.at(id);
}

const std::unordered_map<uint8_t, Player>& GameRoom::getPlayers() const noexcept
{
    return m_players;
}

std::unordered_map<uint8_t, Player>& GameRoom::getPlayers() noexcept
{
    return m_players;
}

bool GameRoom::checkCollision(const Player& player, const Vec2f& newPosition)
{
    Vec2f topLeft{ newPosition - player.getOrigin() };
    Vec2f bottomRight{ topLeft + player.GetSize() };

    if (topLeft.x < 0 || topLeft.y < 0 ||
        bottomRight.x > Level::kWidth * Level::kGridSize ||
        bottomRight.y > Level::kHeight * Level::kGridSize)
    {
        return true;
    }

    auto [topLeftX, topLeftY] = topLeft.toGridCoords(Level::kGridSize);
    auto [bottomRightX, bottomRightY] = bottomRight.toGridCoords(Level::kGridSize);

    for (int x = topLeftX; x <= bottomRightX; ++x)
    {
        for (int y = topLeftY; y <= bottomRightY; ++y)
        {
            const auto& currentObstacle{ m_level[{y, x}] };
            if (!currentObstacle) continue;

            if (!currentObstacle->isPassable() && currentObstacle->collides(topLeft, bottomRight))
            {
                return true;
            }
        }
    }

    return false;
}
