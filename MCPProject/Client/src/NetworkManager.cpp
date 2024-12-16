#include "NetworkManager.h"
#include <cpr/cpr.h>
#include <iostream>

const std::string NetworkManager::kServerUrl{"http://127.0.0.1:18080"};

//TODO: add a logger
//TODO: don't block the main thread waiting for responses
//TODO: add custom json serialization for custom types
NetworkManager::NetworkManager()
    : m_clientVersion{0}
{}

nlohmann::json NetworkManager::join(const Player& player)
{
    nlohmann::json data = {
        {"position", {player.getPosition().x, player.getPosition().y}}
    };

    cpr::Response joinResponse = cpr::Post(
        cpr::Url{kServerUrl + "/join"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{data.dump()}
    );

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

        if (!response.contains("id"))
        {
            std::cout << "Invalid join response format: missing 'id'\n";
            return {};
        }

        std::cout << response["message"] << "\n";
        return response;
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cout << std::format("Error parsing join response: {}\n", error.what());
        return {};
    }
}

//TODO: maybe us std::optional and check in Game to see if the response is empty. nlohmann::json foo.empty() works aswell
nlohmann::json NetworkManager::update()
{
    m_session.SetUrl(cpr::Url{kServerUrl + "/gameState"});
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
            std::cout << std::format("No update needed, clientVersion==serverVersion=={}\n", m_clientVersion);
            return {};
        }

        std::cout << "Update needed\n";
        m_clientVersion = updateResponse["serverVersion"];
        return updateResponse;
    }
    catch (const nlohmann::json::parse_error& error)
    {
        std::cout << std::format("Error parsing join response: {}\n", error.what());
        return {};
    }
}

void NetworkManager::movePlayer(uint16_t clientID, Direction direction, float deltaTime)
{
    nlohmann::json data = {
        {"id", clientID},
        {"direction", direction},
        {"deltaTime", deltaTime}
    };

    m_session.SetUrl(cpr::Url{kServerUrl + "/move"});
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

    std::cout << response.text << "\n";
}
