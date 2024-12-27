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

nlohmann::json GameRoom::getStateResponse(uint32_t clientVersion) const noexcept
{
    nlohmann::json response = {
        {"serverVersion", m_version},
    };

    if (clientVersion != m_version)
    {
        response["levelLayout"] = m_level.getLayout();

        response["players"] = nlohmann::json::array();
        for (const auto& [id, player] : m_players)
        {
            response["players"].push_back({
                {"id", id},
                {"position", {player.getPosition().x, player.getPosition().y}}, // TODO: custom serialization
                {"direction", player.getDirection()}
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
    Vec2f newPosition{ player.getPosition() };

    if (direction != player.getDirection())
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

const std::unordered_map<uint8_t, Player>& GameRoom::getPlayers() const noexcept
{
    return m_players;
}

bool GameRoom::checkCollision(const Player& player, const Vec2f& newPosition)
{
    Vec2f topLeft     { newPosition - player.getOrigin() };
    Vec2f bottomRight { topLeft + player.getSize() };

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
