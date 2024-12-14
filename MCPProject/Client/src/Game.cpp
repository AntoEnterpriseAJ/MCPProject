#include "Game.h"
#include "ResourceManager.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <memory>
#include <chrono>

static uint32_t clientVersion{0};

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"), m_gameState{ GameState::Menu }, m_internalID{0}, m_session{}
{
    ResourceManager& instance = ResourceManager::getInstance();
    instance.loadTextureFromFile("res/textures/plane.png", "player");
    instance.loadTextureFromFile("res/textures/albedo.png", "brick");
    instance.loadTextureFromFile("res/textures/missile.png", "bullet");
    instance.loadTextureFromFile("res/textures/bush.png", "bush");
    instance.loadTextureFromFile("res/textures/unbreakable.png", "unbreakableBrick");
    instance.loadTextureFromFile("res/textures/background.png", "background");
    instance.loadTextureFromFile("res/textures/explosionSheet.png", "explosionSheet");
    instance.loadTextureFromFile("res/textures/bombBrick.png", "bombBrick");
}

uint16_t Game::getWindowWidth()
{
    return kWindowWidth;
}

uint16_t Game::getWindowHeight()
{
    return kWindowHeight;
}

void Game::join(sf::Vector2f position)
{
    nlohmann::json data = {
        {"position", {position.x, position.y}}
    };

    cpr::Response joinResponse = cpr::Post(
        cpr::Url{"http://127.0.0.1:18080/join"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{data.dump()}
    );

    if (joinResponse.status_code != 200)
    {
        std::cout << std::format("There was an error joining. HTTP status: {}, Error: {}\n"
                                , joinResponse.status_code
                                , joinResponse.error.message);
        return;
    }

    nlohmann::json response = nlohmann::json::parse(joinResponse.text);

    m_internalID = response["id"];
    m_players[m_internalID] = Player{position, ResourceManager::getInstance().getTexture("player"), sf::Vector2f{ 39.9f, 39.9f }};
    std::cout << response["message"] << "\n";
}

// TODO: don't block the main thread
void Game::move(Direction direction)
{
    nlohmann::json data = {
        {"id", m_internalID},
        {"direction", direction}
    };

    m_session.SetUrl(cpr::Url{"http://127.0.0.1:18080/move"});
    m_session.SetHeader(cpr::Header{{"Content-Type", "application/json"}});
    m_session.SetBody(cpr::Body{data.dump()});

    cpr::Response response = m_session.Post();
    std::cout << "Move response is ready\n";

    if (response.status_code != 200)
    {
        std::cout << std::format("There was an error moving: HTTP status: {}, Error: {}\n"
                                , response.status_code
                                , response.error.message);
        return;
    }

    std::cout << response.text << "\n";
    return;
}

void Game::update()
{
    m_session.SetUrl(cpr::Url{"http://127.0.0.1:18080/gameState"});
    m_session.SetParameters(cpr::Parameters{{"clientVersion", std::to_string(clientVersion)}});

    cpr::Response response = m_session.Get();
    std::cout << "Update response is ready\n";

    if (response.status_code != cpr::status::HTTP_OK)
    {
        std::cout << std::format("Couldn't retrieve the gamestate. HTTP Status: {}, Error: {}\n"
                                , response.status_code
                                , response.error.message);
        return;
    }

    nlohmann::json updateResponse = nlohmann::json::parse(response.text);
    if (updateResponse["serverVersion"] == clientVersion)
    {
        std::cout << "No update needed\n";
        return;
    }

    std::cout << "Update needed\n";
    std::ranges::for_each(updateResponse["players"], [this](const auto& playerData){
        sf::Vector2f newPosition = {playerData["position"][0], playerData["position"][1]};
        uint16_t playerId = playerData["id"];

        if (!m_players.contains(playerData["id"]))
        {
            m_players[playerId] = {newPosition, ResourceManager::getInstance().getTexture("player"), {39.9f, 39.9f}};
        }

        m_players[playerId].setPosition(newPosition);
    });

    return;
}

void Game::render()
{
    while (m_window.isOpen())
    {
        if (m_gameState == GameState::Menu)
        {
            std::cout << "Join the game? 1-Yes 0-No\n";
            int option;
            std::cin >> option;

            if (option == 1)
            {
                std::cout << "Spawn pos x, y =";
                float x, y;
                std::cin >> x >> y;

                this->join(sf::Vector2f{x, y});
                m_gameState = GameState::Playing;
            }
        }

        if (m_gameState == GameState::Playing)
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        m_window.close();
                    }
                    else if (event.key.code == sf::Keyboard::W)
                    {
                        move(Direction::Up);
                    }
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        move(Direction::Down);
                    }
                    else if (event.key.code == sf::Keyboard::A)
                    {
                        move(Direction::Left);
                    }
                    else if (event.key.code == sf::Keyboard::D)
                    {
                        move(Direction::Right);
                    }
                }
            }

            m_window.clear();
            update();

            std::ranges::for_each(m_players, [this](const auto& entry){
                const auto& [id, player] = entry;
                m_window.draw(player);
            });

            m_window.display();
        }
    }
}