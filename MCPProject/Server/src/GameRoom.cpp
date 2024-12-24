#include "GameRoom.h"

GameRoom::GameRoom()
    : m_idCounter{0}, m_roomID{0}, m_version{0}, m_players{}
{}

GameRoom::GameRoom(uint8_t m_roomID)
    : m_roomID{m_roomID}, m_idCounter{0}, m_version{0}, m_players{}, m_level{}
{
    m_level.load();
}

uint8_t GameRoom::addPlayer(const Player::Position& position)
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
        for (const auto& [id, player]: m_players)
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
    m_players[playerID].move(direction, deltaTime);
    m_version = (m_version + 1) % kMaxVersion;
}

Level GameRoom::getLevel() const noexcept
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
