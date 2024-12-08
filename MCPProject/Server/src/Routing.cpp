#include "Routing.h"
#include "nlohmann/json.hpp"
#include "Player.h"
#include <vector>

void Routing::run()
{
    CROW_ROUTE(m_server, "/greet").methods(crow::HTTPMethod::Get)
    ([](){
        return crow::response("Welcome to the server!");
    });

    static std::vector<Player> players;

    CROW_ROUTE(m_server, "/join").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto data = nlohmann::json::parse(req.body);

        if (!data.contains("position") && data["position"].size() != 2)
        {
            return crow::response(400, "invalid request body");
        }

        Player::Position position{data["position"][0], data["position"][1]};

        players.push_back(Player{position});

        return crow::response(200);
    });

    CROW_ROUTE(m_server, "/players").methods(crow::HTTPMethod::GET)
    ([](){
        nlohmann::json response = nlohmann::json::array();

        for (const Player& player : players)
        {
            response.push_back({
                {"position", {player.getPosition().first, player.getPosition().second}}
            });
        }

        return crow::response(response.dump());
    });

    m_server.port(kPort).multithreaded().run();
}
