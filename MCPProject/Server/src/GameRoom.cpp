#include "GameRoom.h"
#include "ObstacleType.h"
#include "PickablePowerUp.h"
#include <iostream>

GameRoom::GameRoom()
    : m_idCounter{ 0 }, m_roomID{ 0 }, m_version{ 1 }
    , m_players{}, m_state{ GameRoomState::Waiting }, m_updatedScore{ false }
{}

GameRoom::GameRoom(uint8_t m_roomID)
    : m_roomID{ m_roomID }, m_idCounter{ 0 }, m_version{ 0 }
    , m_players{}, m_level{}, m_state{ GameRoomState::Waiting }, m_updatedScore{ false }
{
    m_level.load();
}

uint8_t GameRoom::addPlayer(uint16_t databaseID)
{
    m_players.emplace(m_idCounter, m_respawnPositions[m_idCounter]);
    m_players.at(m_idCounter).setRespawnPosition(m_respawnPositions[m_idCounter]);
    m_players.at(m_idCounter).setDatabaseID(databaseID);

    m_version = (m_version + 1) % kMaxVersion;
    return m_idCounter++;
}

nlohmann::json GameRoom::getGameStateResponse(uint32_t clientVersion) noexcept
{
    nlohmann::json response = {
        {"serverVersion", m_version},
        {"roomState", m_state}
    };

    update();
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

        response["bullets"] = nlohmann::json::array();
        for (const auto& bullet : m_bulletManager.getBullets())
        {
            response["bullets"].push_back({
                {"position", {bullet->GetPosition().x, bullet->GetPosition().y}},
                {"direction", bullet->getDirection()},
                });
        }

        response["powerUps"] = nlohmann::json::array();
        for (const auto& powerUp : m_powerUpManager.getCollectablePowerUps())
        {
            response["powerUps"].push_back({
                {"effect", powerUp.GetEffect()},
                {"position", {powerUp.GetPosition().x, powerUp.GetPosition().y}},
                {"size", {PickablePowerUp::kPowerUpSize.x, PickablePowerUp::kPowerUpSize.y}}
                });
        }
    }

    return response;
}

bool GameRoom::getUpdatedScore() const noexcept
{
    return m_updatedScore;
}

GameRoomState GameRoom::getState() const noexcept
{
    return m_state;
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
        newPosition.y -= player.getSpeed() * deltaTime;
    }
    else if (direction == Direction::Down)
    {
        newPosition.y += player.getSpeed() * deltaTime;
    }
    else if (direction == Direction::Left)
    {
        newPosition.x -= player.getSpeed() * deltaTime;
    }
    else if (direction == Direction::Right)
    {
        newPosition.x += player.getSpeed() * deltaTime;
    }

    if (!checkCollision(player, newPosition))
    {
        player.setPosition(newPosition);
    }

    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::setState(GameRoomState state)
{
    m_state = state;
}

void GameRoom::shoot(uint8_t playerID)
{
    Player& player{ m_players.at(playerID) };

    if (!player.canShoot()) return;

    player.resetShootCooldown();
    Vec2f offset{ 0.0f, 0.0f };
    Bullet bullet{ {}, Direction::Up, {} };

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

    m_bulletManager.addBullet(std::make_unique<Bullet>(
        player.GetPosition() + offset,
        player.GetDirection(),
        playerID,
        Vec2f{Bullet::kBulletSizeX, Bullet::kBulletSizeY},
        Bullet::kBulletDamage * player.getDamageMultiplier()
    ));

    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::tryToStart()
{
    if (m_players.size() >= kMinPlayers && !m_waitingToStart)
    {
        std::cout << std::format("Room({}): Minimum players reached, countdown started!\n", m_roomID);
        m_waitingToStart = true;
        m_roomStartTimer = std::chrono::steady_clock::now();
    }

    if (m_waitingToStart)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - m_roomStartTimer).count();

        if (m_players.size() < kMinPlayers)
        {
            std::cout << std::format("Room({}): Not enough players! Resetting countdown...\n", m_roomID);
            m_waitingToStart = false;
            return;
        }

        if (elapsed >= kWaitingTime)
        {
            std::cout << std::format("Room({}): Countdown finished, game starting!\n", m_roomID);
            m_state = GameRoomState::Playing;
            m_waitingToStart = false;
        }
    }
}

void GameRoom::checkWinCondition()
{
    if (m_state != GameRoomState::Playing) return;

    int stillPlayingCount = 0;
    uint8_t winnerID = 0;

    for (const auto& [id, player] : m_players)
    {
        if (!player.isEliminated())
        {
            stillPlayingCount++;
            winnerID = id;
            if (stillPlayingCount > 1)
            {
                return;
            }
        }
    }

    if (stillPlayingCount == 1)
    {
        std::cout << std::format("Room({}): Player {} won the game!\n", m_roomID, winnerID);
    }
    else
    {
        std::cout << std::format("Room({}): All players eliminated. No winner!\n", m_roomID);
    }

    m_state = GameRoomState::Finished;
    m_eliminatedPlayers.push_back(winnerID);
    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::update()
{
    updateBullets();
    updatePlayerStates();
    m_powerUpManager.update(m_players, m_level.getLayout());
    updatePlayersPowerUps();
    updateEliminatedPlayers();
    checkWinCondition();
    //m_version = (m_version + 1) % kMaxVersion; TODO: for powerups
}

void GameRoom::setUpdatedScore(bool updatedScore)
{
    m_updatedScore = updatedScore;
}

void GameRoom::updatePlayerStates()
{
    bool updated = false;

    auto respawnablePlayers = m_players
        | std::views::filter([](const auto& pair) {
            return !pair.second.isAlive() && pair.second.canRespawn();
        });

    for (auto& [id, player] : respawnablePlayers)
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
    float deltaTime = std::chrono::duration<float>(now - m_deltaTime).count();
    m_deltaTime = now;
    m_bulletManager.update(m_level, m_players, deltaTime);

    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::updatePlayersPowerUps()
{
    for (auto& player : m_players | std::views::values)
    {
        player.updatePowerUps();
    }
}

void GameRoom::updateEliminatedPlayers()
{
    auto eliminatedPlayers = m_players
        | std::views::filter([](const auto& pair) {
        return pair.second.isEliminated();
            });

    for (auto& [id, player] : eliminatedPlayers)
    {
        if (std::ranges::find(m_eliminatedPlayers, id) == m_eliminatedPlayers.end())
        {
            m_eliminatedPlayers.push_back(id);
        }
    }
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

const std::vector<uint8_t>& GameRoom::getEliminatedPlayers() const noexcept
{
    return m_eliminatedPlayers;
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
