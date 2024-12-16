#include "Game.h"
#include "ResourceManager.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <memory>
#include <chrono>

static uint32_t clientVersion{0};

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"), m_gameState{ GameState::Menu }, m_internalID{0}
{
    ResourceManager& instance = ResourceManager::getInstance();
    instance.loadTextureFromFile("res/textures/penguin1.png", "player");
    instance.loadTextureFromFile("res/textures/ice_block.png", "brick");
    instance.loadTextureFromFile("res/textures/ice.png", "bullet");
    instance.loadTextureFromFile("res/textures/bush.png", "bush");
    instance.loadTextureFromFile("res/textures/unbreakable.png", "unbreakableBrick");
    instance.loadTextureFromFile("res/textures/ice_map.png", "background");
    instance.loadTextureFromFile("res/textures/explosion.png", "explosionSheet");
    instance.loadTextureFromFile("res/textures/bombBrick.png", "bombBrick");

    m_level.load();
}

uint16_t Game::getWindowWidth()
{
    return kWindowWidth;
}

uint16_t Game::getWindowHeight()
{
    return kWindowHeight;
}

void Game::handleInputs(float deltaTime)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            m_window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(Direction::Up, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move(Direction::Down, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(Direction::Left, deltaTime);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(Direction::Right, deltaTime);
    }
}

void Game::join(const Player& player)
{
    nlohmann::json response = m_networkManager.join(player);

    m_internalID = response["id"];
    m_players[m_internalID] = player;
}

void Game::move(Direction direction, float deltaTime)
{
    m_networkManager.movePlayer(m_internalID, direction, deltaTime);
    return;
}

void Game::update()
{
    nlohmann::json updateResponse = m_networkManager.update();

    if (updateResponse.empty())
    {
        return;
    }

    std::ranges::for_each(updateResponse["players"], [this](const auto& playerData){
        sf::Vector2f newPosition = {playerData["position"][0], playerData["position"][1]};
        uint16_t playerId = playerData["id"];
        Direction direction = playerData["direction"];

        if (!m_players.contains(playerId))
        {
            m_players[playerId] = {newPosition, ResourceManager::getInstance().getTexture("player"), sf::Vector2f{39.9f, 39.9f}};
        }

        m_players[playerId].setPosition(newPosition);
        m_players[playerId].setDirection(direction);
    });

    return;
}

void Game::render()
{
    while (m_window.isOpen())
    {
        float deltaTime = m_lastFrametimeClock.restart().asSeconds();

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

                Player player{sf::Vector2f{x, y}, ResourceManager::getInstance().getTexture("player"), sf::Vector2f{39.9f, 39.9f}};

                this->join(player);
                m_gameState = GameState::Playing;
            }
        }

        if (m_gameState == GameState::Playing)
        {
            m_window.clear();
            handleInputs(deltaTime);
            update();

            m_window.draw(m_level);
            std::ranges::for_each(m_players, [this](const auto& entry){
                const auto& [id, player] = entry;
                m_window.draw(player);
            });

            m_window.display();
        }
    }
}