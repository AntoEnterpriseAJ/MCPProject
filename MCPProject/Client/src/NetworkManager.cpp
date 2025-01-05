#include "NetworkManager.h"
#include <cpr/cpr.h>
#include <iostream>
#include <format>

const std::string NetworkManager::kServerUrl{"http://127.0.0.1:18080"};

//TODO: add a logger
//TODO: don't block the main thread waiting for responses (for now it's fine)
//TODO: add custom json serialization for custom types
NetworkManager::NetworkManager()
    : m_clientVersion{0}, m_URL{kServerUrl}, m_currentRoomID{0}
{}

void NetworkManager::createRoom()
{
    cpr::Response createResponse = cpr::Post(
        cpr::Url{m_URL.addToPath("createRoom").build()}
    );

    if (createResponse.status_code != cpr::status::HTTP_OK)
    {
        std::cout << std::format("There was an error joining. HTTP status: {}, Error: {}\n"
                                , createResponse.status_code
                                , createResponse.error.message);
    }

    try
    {
        nlohmann::json response = nlohmann::json::parse(createResponse.text);

        if (!response.contains("roomID"))
        {
            std::cout << "Invalid join response format: missing 'roomID'\n";
            return;
        }

        m_currentRoomID = response["roomID"];
        std::cout << std::format("Created room {}\n", response["roomID"].get<uint8_t>());
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cout << std::format("Error parsing createRoom response: {}\n", error.what());
    }
}

nlohmann::json NetworkManager::join(const Player& player, uint8_t roomID)
{
    std::cout << "Trying to join...\n";
    nlohmann::json data {
        {"position", {player.GetPosition().x, player.GetPosition().y}}
    };

    cpr::Response joinResponse = cpr::Post(
        cpr::Url{m_URL.addToPath("joinRoom").addToPath(std::to_string(roomID)).build()},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{data.dump()}
    );
    
    std::cout << m_URL.addToPath("joinRoom").addToPath(std::to_string(roomID)).build() << "\n";

    if (joinResponse.status_code != cpr::status::HTTP_OK)
    {
        std::cout << std::format("There was an error joining. HTTP status: {}, Error: {}\n"
                                , joinResponse.status_code
                                , joinResponse.error.message);
        return {};
    }
    
    try
    {
        nlohmann::json response = nlohmann::json::parse(joinResponse.text);

        if (!response.contains("playerID"))
        {
            std::cout << "Invalid join response format: missing 'playerID'\n";
            return {};
        }

        std::cout << response["message"] << "\n";
        m_currentRoomID = roomID;
        return response;
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cout << std::format("Error parsing join response: {}\n", error.what());
        return {};
    }
}

nlohmann::json NetworkManager::update()
{
    m_session.SetUrl(
        cpr::Url{m_URL.addToPath("room").addToPath(std::to_string(m_currentRoomID)).addToPath("gameState").build()}
    );
    m_session.SetParameters(cpr::Parameters{{"clientVersion", std::to_string(m_clientVersion)}});

    cpr::Response response = m_session.Get();

    if (response.status_code != cpr::status::HTTP_OK)
    {
        std::cout << std::format("Couldn't retrieve the gamestate. HTTP Status: {}, Error: {}\n"
                                , response.status_code
                                , response.error.message);
        return {};
    }
    
    try
    {
        nlohmann::json updateResponse = nlohmann::json::parse(response.text);
        if (!updateResponse.contains("serverVersion"))
        {
            std::cout << "Invalid update response format: missing 'serverVersion'\n";
            return {};
        }


        if (updateResponse["serverVersion"] == m_clientVersion)
        {
            //std::cout << std::format("No update needed, clientVersion==serverVersion=={}\n", m_clientVersion);
            return {};
        }

        //std::cout << "Update needed\n";
        m_clientVersion = updateResponse["serverVersion"];
        return updateResponse;
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cout << std::format("Error parsing join response: {}\n", error.what());
        return {};
    }
}

nlohmann::json NetworkManager::getExistingRooms()
{
    cpr::Response response = cpr::Get(
        cpr::Url{m_URL.addToPath("getRooms").build()}
    );

    if (response.status_code != cpr::status::HTTP_OK) {
                std::cout << std::format("Couldn't retrieve the existings rooms. HTTP Status: {}, Error: {}\n"
                                , response.status_code
                                , response.error.message);
        return {};
    }

    try
    {
        return nlohmann::json::parse(response.text);
    }
    catch (const nlohmann::json::parse_error& e)
    {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }
}

void NetworkManager::movePlayer(uint16_t clientID, Direction direction, float deltaTime)
{
    nlohmann::json data = {
        {"id", clientID},
        {"direction", direction},
        {"deltaTime", deltaTime}
    };

    m_session.SetUrl(
        cpr::Url{m_URL.addToPath("room").addToPath(std::to_string(m_currentRoomID)).addToPath("move").build()}
    );
    m_session.SetHeader(cpr::Header{{"Content-Type", "application/json"}});
    m_session.SetBody(cpr::Body{data.dump()});

    cpr::Response response = m_session.Post();

    if (response.status_code != cpr::status::HTTP_OK)
    {
        std::cout << std::format("There was an error moving: HTTP status: {}, Error: {}\n"
                                , response.status_code
                                , response.error.message);
        return;
    }

    //std::cout << response.text << "\n";
}

void NetworkManager::setRoomID(uint8_t roomID)
{
    m_currentRoomID = roomID;
}

uint8_t NetworkManager::getCurrentRoomID() const
{
    return m_currentRoomID;
}
