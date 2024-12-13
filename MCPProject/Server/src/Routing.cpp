#include "Routing.h"
#include "nlohmann/json.hpp"

Routing::Routing()
    : m_idCounter{ 0 }, m_server{}, m_players{}, m_version{0}
{}

void Routing::run()
{
    CROW_ROUTE(m_server, "/greet").methods(crow::HTTPMethod::Get)
    ([](){
        return crow::response("Welcome to the server!");
    });

    CROW_ROUTE(m_server, "/join").methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req){
        auto data = nlohmann::json::parse(req.body);

        if (!data.contains("position") && data["position"].is_array() && data["position"].size() != 2)
        {
            return crow::response(400, "invalid request body");
        }

        Player::Position position{data["position"][0], data["position"][1]};
        m_players[m_idCounter] = Player{position, m_idCounter};

        nlohmann::json response = {
            {"id", m_idCounter},
            {"message", "Player joined succesfully with ID " + std::to_string(m_idCounter)}
        };

        m_idCounter++;
        m_version = (m_version + 1) % kMaxVersion;
        return crow::response(200, response.dump());
    });

    CROW_ROUTE(m_server, "/gameState").methods(crow::HTTPMethod::GET)
    ([this](const crow::request& req){
        uint32_t clientVersion = std::stoi(req.url_params.get("clientVersion"));

        nlohmann::json response = {
            {"serverVersion", m_version},
        };

        if (clientVersion != m_version)
        {
            response["players"] = nlohmann::json::array();
            for (const auto& [id, player]: m_players)
            {
                response["players"].push_back({
                    {"id", id},
                    {"position", {player.getPosition().first, player.getPosition().second}}
                });
            }
        }

        return crow::response(response.dump());
    });

    CROW_ROUTE(m_server, "/move").methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req){
        auto data = nlohmann::json::parse(req.body);

        if (!data.contains("id") || !data.contains("direction"))
        {
            return crow::response(400, "invalid request body");
        }

        std::string direction{data["direction"]};
        float xOffset{0}, yOffset{0};
        if (direction == "up")
        {
            yOffset -= 10.0f;
        }
        else if (direction == "down")
        {
            yOffset += 10.0f;
        }
        else if (direction == "left")
        {
            xOffset -= 10.0f;
        }
        else if (direction == "right")
        {
            xOffset += 10.0f;
        }

        Player::Position oldPos = m_players[data["id"]].getPosition();
        Player::Position newPosition = {oldPos.first + xOffset, oldPos.second + yOffset};

        if (m_players.contains(data["id"]))
        {
            m_players[data["id"]].setPosition(newPosition);
        }
        else
        {
            return crow::response(400, "the server doesn't have this player");
        }
        
        m_version = (m_version + 1) % kMaxVersion;
        return crow::response(200, "the move was succesful");
    });

   crow::logger::setLogLevel(crow::LogLevel::Critical);
   m_server.port(kPort).multithreaded().run();
}
