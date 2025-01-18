#include "Game.h"
#include <nlohmann/json.hpp>;
#include <cpr/cpr.h>;
#include <iostream>;
#include <memory>;
#include <chrono>;
#include "ResourceManager.h";


static uint32_t clientVersion{0};

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"), m_gameState{ GameState::Menu }
    , m_internalID{ 0 }, m_bulletManager{}, m_powerUpManager{}
{
    ResourceManager& instance = ResourceManager::getInstance();
    instance.loadTextureFromFile("res/textures/penguin1.png", "player1");
    instance.loadTextureFromFile("res/textures/penguin2.png", "player2");
    instance.loadTextureFromFile("res/textures/penguin3.png", "player3");
    instance.loadTextureFromFile("res/textures/penguin4.png", "player4");
    instance.loadTextureFromFile("res/textures/ice_block.png", "brick");
    instance.loadTextureFromFile("res/textures/ice.png", "bullet");
    instance.loadTextureFromFile("res/textures/bush.png", "bush");
    instance.loadTextureFromFile("res/textures/unbreakable.png", "unbreakableBrick");
    instance.loadTextureFromFile("res/textures/ice_map.png", "background");
    instance.loadTextureFromFile("res/textures/explosion.png", "explosionSheet");
    instance.loadTextureFromFile("res/textures/bombBrick.png", "bombBrick");

    m_level.init();
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

    if (!m_window.hasFocus() || !m_players[m_internalID].isAlive())
    {
        return;
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_networkManager.shoot(m_internalID);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        buyPowerUp(PowerUpEffect::DamageUp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        buyPowerUp(PowerUpEffect::ReduceShootCooldown);
    }
}

void Game::createRoom()
{
    m_networkManager.createRoom();
}

void Game::buyPowerUp(PowerUpEffect powerUp)
{
    m_networkManager.buyPowerUp(m_internalID, m_databaseID, powerUp);
}

bool Game::join(uint8_t roomID)
{
    nlohmann::json response = m_networkManager.join(roomID);

    if (response.empty())
    {
        return false;
    }

    m_internalID = response["playerID"];
    return true;
}

bool Game::login(const std::string& username, const std::string& password)
{
    nlohmann::json response = m_networkManager.login(username, password);
    if (response.empty())
    {
        std::cout << "Login failed\n";
        return false;
    }

    std::cout << "Login successful\n";
    return true;
}

bool Game::registerUser(const std::string& username, const std::string& password)
{
    nlohmann::json response = m_networkManager.registerUser(username, password);
    if (response.empty())
    {
        std::cout << "Register failed\n";
        return false;
    }

    std::cout << "Register successful\n";
    return true;
}

void Game::move(Direction direction, float deltaTime)
{
    m_networkManager.movePlayer(m_internalID, direction, deltaTime);
}

void Game::displayRooms()
{
    std::cout << m_networkManager.getExistingRooms().dump() << "\n";
}

void Game::handleMenu()
{
    std::cout << "Welcome to the game\n";
    std::cout << "1.Login\n2.Register\n";

    bool authenticated = false;
    int option;
    std::cin >> option;

    if (option == 1)
    {
        std::string username, password;
        std::cout << "username=";
        std::cin >> username;
        std::cout << "password=";
        std::cin >> password;
        if (login(username, password))
        {
            m_gameState = GameState::Playing;
            authenticated = true;
        }
    }
    else if (option == 2)
    {
        std::string username, password;
        std::cout << "username=";
        std::cin >> username;
        std::cout << "password=";
        std::cin >> password;
        if (registerUser(username, password))
        {
            m_gameState = GameState::Playing;
            authenticated = true;
        }
    }

    if (!authenticated)
    {
        return;
    }

    std::cout << "1.Create a new room\n2.Join an existing room\n3.Display existing rooms\n";
    std::cin >> option;

    if (option == 1)
    {
        this->createRoom();
        join(m_networkManager.getCurrentRoomID());
                
        m_gameState = GameState::Playing;
    }
    else if (option == 2)
    {
        int roomID;
        std::cout << "room id=";
        std::cin >> roomID;

        if (!join(roomID))
        {
            std::cout << "Something went wrong\n";
            return;
        }

        m_gameState = GameState::Playing;
    }
    else if (option == 3)
    {
        displayRooms();
    }
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
        uint16_t    playerId  { playerData["id"] };
        Direction   direction { playerData["direction"] };
        uint16_t    lives     { playerData["lives"] };
        uint16_t    health    { playerData["health"] };
        PlayerState state     { playerData["state"] };
        uint16_t    points    { playerData["points"] };


        if (!m_players.contains(playerId))
        {
            std::string textureKey = "player" + std::to_string(playerId + 1);
            m_players[playerId] = { newPosition, ResourceManager::getInstance().getTexture(textureKey), sf::Vector2f{39.9f, 39.9f} };
        }


        m_players[playerId].setPosition(newPosition);
        m_players[playerId].setDirection(direction);
        m_players[playerId].setLives(lives);
        m_players[playerId].setHealth(health);
        m_players[playerId].setState(state);
        m_players[playerId].setPoints(points);
    });

    m_bulletManager.clearBullets();
    std::ranges::for_each(updateResponse["bullets"], [this](const auto& bulletData) {
        sf::Vector2f position = { bulletData["position"][0], bulletData["position"][1] };
        Direction direction = bulletData["direction"];
        m_bulletManager.addBullet(
            std::make_unique<Bullet>(position, ResourceManager::getInstance().getTexture("bullet"), direction));
    });

    m_powerUpManager.clearPowerUps();
    std::ranges::for_each(updateResponse["powerUps"], [this](const auto& powerUpData) {
        sf::Vector2f position { powerUpData["position"][0], powerUpData["position"][1] };
        PowerUpEffect effect{ powerUpData["effect"]};
        sf::Vector2f size{ powerUpData["size"][0], powerUpData["size"][1] };

        m_powerUpManager.addPowerUp(position, size, effect);
    });

    m_level.update(updateResponse["levelLayout"]);

    return;
}

void Game::render()
{
    sf::Clock logClock;

    while (m_window.isOpen())
    {
        float deltaTime = m_lastFrametimeClock.restart().asSeconds();

        if (m_gameState == GameState::Menu)
        {
            handleMenu();
        }

        if (m_gameState == GameState::Playing)
        {
            m_window.clear();
            handleInputs(deltaTime);
            update();

            m_level.drawBackground(m_window);

            std::ranges::for_each(m_players | std::views::values | std::views::filter([](const Player& player) {
                return player.isAlive();
                }),
                [this](const Player& player) {
                    m_window.draw(player);
                });

            m_bulletManager.draw(m_window);
            m_powerUpManager.draw(m_window);

            m_window.draw(m_level);

            m_window.display();

            if (logClock.getElapsedTime().asSeconds() >= 3.0f)
            {
                std::cout << "Player Points:\n";

                std::ranges::for_each(m_players, [](const auto& pair) {
                    auto [playerId, player] = pair;
                    std::cout << std::format("Player id({}), Health({}), Lives({}), Points: {}\n",
                        playerId, player.GetHealth(), player.GetLives(), player.GetPoints());
                    });

                std::cout << "--------------------------------------------------\n";
                logClock.restart();
            }
        }
    }
}