#include "GameRoom.h"
#include "ObstacleType.h"

#include <iostream>

GameRoom::GameRoom()
    : m_idCounter{ 0 }, m_roomID{ 0 }, m_version{ 0 }, m_players{}
{}

GameRoom::GameRoom(uint8_t m_roomID)
    : m_roomID{ m_roomID }, m_idCounter{ 0 }, m_version{ 0 }, m_players{}, m_level{}
{
    m_level.load();
}

uint8_t GameRoom::addPlayer(const Vec2f& position)
{
    m_players.emplace(m_idCounter, position);
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
                {"direction", player.GetDirection()}
                });
        }

        update();
        response["bullets"] = nlohmann::json::array();
        for (const auto& bullet : m_bulletManager.getBullets())
        {
            response["bullets"].push_back({
                {"position", {bullet->getPosition().x, bullet->getPosition().y}},
                {"direction", bullet->getDirection()}
                });
        }

        std::cout << "Currently we have " << m_bulletManager.getBullets().size() << " bullets\n";
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

    player.restartCooldown();
    Vec2f offset{ 0.0f, 0.0f };
    switch (player.getDirection())
    {
    case Direction::Up:
        offset = { 0.0f, -Player::kPlayerSizeY };
        break;
    case Direction::Down:
        offset = { 0.0f, Player::kPlayerSizeY };
        break;
    case Direction::Left:
        offset = { -Player::kPlayerSizeX, 0.0f };
        break;
    case Direction::Right:
        offset = { Player::kPlayerSizeX, 0.0f };
        break;
    }

    m_bulletManager.addBullet(std::make_unique<Bullet>(player.getPosition() + offset, player.getDirection()));
    m_version = (m_version + 1) % kMaxVersion;
}

void GameRoom::update()
{
    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - m_lastUpdated).count();
    m_lastUpdated = now;
    m_version = (m_version + 1) % kMaxVersion;

    m_bulletManager.update(m_level, deltaTime);
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

bool GameRoom::checkCollision(const Player& player, const Vec2f& newPosition)
{
    Vec2f topLeft     { newPosition - player.getOrigin() };
    Vec2f bottomRight { topLeft + player.GetSize() };

    int topLeftX     = static_cast<int>(std::floor(topLeft.x / Level::kGridSize));
    int topLeftY     = static_cast<int>(std::floor(topLeft.y / Level::kGridSize));
    int bottomRightX = static_cast<int>(std::floor(bottomRight.x / Level::kGridSize));
    int bottomRightY = static_cast<int>(std::floor(bottomRight.y / Level::kGridSize));

    for (int x = topLeftX; x <= bottomRightX; ++x)
    {
        for (int y = topLeftY; y <= bottomRightY; ++y)
        {
            const auto& currentObstacle {m_level[{y, x}]};
            if (!currentObstacle) continue;

            if (!currentObstacle->isPassable() && currentObstacle->collides(topLeft, bottomRight))
            {
                return true;
            }
        }
    }

    return false;
}
