#include "Routing.h"
#include "nlohmann/json.hpp"
#include <format>
#include <algorithm>
#include <ranges>

Routing::Routing()
    : m_roomIDCounter{ 0 }, m_server{}, m_dbManager{ "game.db" }
{}

void Routing::run()
{
    CROW_ROUTE(m_server, "/greet").methods(crow::HTTPMethod::Get)
    ([](){
        return crow::response("Welcome to the server!");
    });

    CROW_ROUTE(m_server, "/getRooms").methods(crow::HTTPMethod::GET)
    ([this]() {
        nlohmann::json response;
        response["rooms"] = nlohmann::json::array();

        std::ranges::for_each(m_rooms | std::ranges::views::values, [&response](const auto& room) {
            response["rooms"].emplace_back(nlohmann::json{
                {"roomID", room.getID()}
            });
        });

        return crow::response(200, response.dump());
    });

    CROW_ROUTE(m_server, "/createRoom").methods(crow::HTTPMethod::Post)
    ([this](){
        m_rooms.emplace(m_roomIDCounter, m_roomIDCounter);

        nlohmann::json response{
            {"roomID", m_roomIDCounter},
        };

        m_roomIDCounter++;
        return crow::response(200, response.dump());
    });

    CROW_ROUTE(m_server, "/joinRoom/<int>").methods(crow::HTTPMethod::Post)
    ([this](const crow::request& req, uint8_t roomID){
        if (!m_rooms.contains(roomID))
        {
            return crow::response(404, "Room not found");
        }

        if (m_rooms[roomID].getPlayers().size() >= GameRoom::kMaxPlayers)
        {
            return crow::response(400, "Room is full");
        }

        auto data = nlohmann::json::parse(req.body); // TODO: fix, currently not used
        
        uint8_t playerID = m_rooms[roomID].addPlayer(); 
        nlohmann::json response = {
            {"playerID", playerID},
            {"message", std::format("Player {} joined room {}", playerID, roomID)}
        };

        return crow::response(200, response.dump());
    });

    CROW_ROUTE(m_server, "/room/<int>/gameState").methods(crow::HTTPMethod::Get)
    ([this](const crow::request& req, uint8_t roomID){
        if (!m_rooms.contains(roomID))
        {
            return crow::response(404, "room not found");
        }

        if (!req.url_params.get("clientVersion"))
        {
            return crow::response(400, "clientVersion parameter missing");
        }

        uint32_t clientVersion = std::stoi(req.url_params.get("clientVersion"));
        return crow::response(200, m_rooms.at(roomID).getStateResponse(clientVersion).dump());
    });

    CROW_ROUTE(m_server, "/room/<int>/move").methods(crow::HTTPMethod::Post)
    ([this](const crow::request& req, uint8_t roomID){
        if (!m_rooms.contains(roomID))
        {
            return crow::response(404, "room not found");
        }

        auto data = nlohmann::json::parse(req.body);
        if (!data.contains("id") || !data.contains("direction") || !data.contains("deltaTime"))
        {
            return crow::response(400, "invalid request body");
        }

        m_rooms[roomID].move(data["id"], data["direction"].get<Direction>(), data["deltaTime"]);
        return crow::response(200, "the move was successful");
    });

    CROW_ROUTE(m_server, "/room/<int>/shoot").methods(crow::HTTPMethod::Post)
        ([this](const crow::request& req, uint8_t roomID) {
        if (!m_rooms.contains(roomID))
        {
            return crow::response(404, "room not found");
        }

        auto data = nlohmann::json::parse(req.body);
        if (!data.contains("id"))
        {
            return crow::response(400, "invalid request body");
        }

        m_rooms[roomID].shoot(data["id"]);
        return crow::response(200, "the shoot was successful");
    });

    CROW_ROUTE(m_server, "/room/<int>/buyPowerUp").methods(crow::HTTPMethod::Post)
        ([this](const crow::request& req, uint8_t roomID) {
        if (!m_rooms.contains(roomID))
        {
            return crow::response(404, "room not found");
        }
        auto data = nlohmann::json::parse(req.body);
        if (!data.contains("id") || !data.contains("databaseID") || !data.contains("powerUp"))
        {
            return crow::response(400, "invalid request body");
        }

        uint8_t playerID      { data["id"] };
        uint16_t databaseID   { data["databaseID"] };
        PowerUpEffect powerUp { data["powerUp"].get<PowerUpEffect>() };

        Player& player{ m_rooms[roomID].getPlayer(playerID) };

        uint16_t currentPoints{ player.GetPoints() };
        if (currentPoints < PowerUp::getCost(powerUp))
        {
            return crow::response(400, "not enough points to buy the power up");
        }

        player.setPoints(currentPoints - PowerUp::getCost(powerUp));

        m_rooms[roomID].getPlayer(playerID).addPowerUp(
            std::make_unique<PowerUp>(powerUp, PowerUp::kDefaultDuration)
        );

        return crow::response(200, "the power up was bought successfully");
     });

    CROW_ROUTE(m_server, "/login").methods(crow::HTTPMethod::Post)
        ([this](const crow::request& req) {
        auto data = nlohmann::json::parse(req.body);
        if (!data.contains("username") || !data.contains("password"))
        {
            return crow::response(400, "invalid request body");
        }

        if (!m_dbManager.userExists(data["username"]))
        {
            return crow::response(404, "can't log in, username not found");
        }

        if (!m_dbManager.verifyCredentials(data["username"], data["password"]))
        {
            return crow::response(401, "wrong username or password");
        }

        // TODO: if the databaseID was already assigned...
        // there shouldn't be more people on the same acc

        nlohmann::json response{
            {"message", "login successful"},
            {"databaseID", m_dbManager.getUserID(data["username"])},
        };

        return crow::response(200, response.dump());
    });

    CROW_ROUTE(m_server, "/register").methods(crow::HTTPMethod::Post)
        ([this](const crow::request& req) {
        auto data = nlohmann::json::parse(req.body);
        if (!data.contains("username") || !data.contains("password"))
        {
            return crow::response(400, "invalid request body");
        }
        if (m_dbManager.userExists(data["username"]))
        {
            return crow::response(400, "username already exists");
        }
        if (!m_dbManager.addUser(data["username"], data["password"]))
        {
            return crow::response(500, "failed to add user");
        }

        nlohmann::json response{
            {"message", "user registered successfully"},
            {"databaseID", m_dbManager.getUserID(data["username"])},
        };

        return crow::response(200, response.dump());
    });

   crow::logger::setLogLevel(crow::LogLevel::Critical);
   m_server.port(kPort).run();
}
