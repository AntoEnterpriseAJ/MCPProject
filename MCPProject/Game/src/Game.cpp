#include "Game.h"
#include "ResourceManager.h"
#include "Explosion.h"
#include <iostream>

#include "PowerUpManager.h"

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test")
    , m_level{}
    , m_menu{ kWindowWidth, kWindowHeight }
    , m_loginWindow{ kWindowWidth, kWindowHeight }
    , m_gameState{ GameState::Menu }
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
    instance.loadMusicFromFile("res/sfx/mainLoop.wav", m_backgroundMusic);
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.play();

    insertPlayer(
        sf::Vector2f{ 100.0f, 80.0f },
        ResourceManager::getInstance().getTexture("player"),
        sf::Vector2f{ 39.9f, 39.9f }
    );

    m_level.load();
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

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            m_window.close();
        }

        for (auto& player : m_players) 
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            {
                if (player.CanShoot()) 
                {
                    Direction dir = player.GetDirection();
                    sf::Vector2f offset{ 0.0f, 0.0f };
                    float bulletOffsetDistance = 20.0f;

                    switch (player.GetDirection()) 
                    {
                    case Direction::Up:
                        offset.y = -bulletOffsetDistance;
                        break;
                    case Direction::Down:
                        offset.y = bulletOffsetDistance;
                        break;
                    case Direction::Left:
                        offset.x = -bulletOffsetDistance;
                        break;
                    case Direction::Right:
                        offset.x = bulletOffsetDistance;
                        break;
                    }

                    auto bullet = std::make_unique<Bullet>(
                        player.GetPosition() + offset,
                        ResourceManager::getInstance().getTexture("bullet"),
                        player.GetDirection()
                    );

                    m_bulletManager.addBullet(std::move(bullet));
                    ResourceManager::playSound("res/sfx/shooting.wav");
                    player.RestartCooldown();
                    
                }
            }
        }


    }

    for (auto& player : m_players) 
    {
        player.Update(deltaTime);
    }
}

void Game::insertPlayer(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size) 
{
    m_players.emplace_back(pos, texture, size);
}

uint16_t Game::getWindowWidth() 
{
    return kWindowWidth;
}

uint16_t Game::getWindowHeight() 
{
    return kWindowHeight;
}

void Game::render() 
{
    while (m_window.isOpen()) 
    {
        float deltaTime = m_lastFrameTimeClock.restart().asSeconds();

        if (m_gameState == GameState::Menu)
        {
            sf::Event event;
            while (m_window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed) 
                {
                    m_window.close();
                }
                m_menu.handleEvent(m_window, event);
            }

            m_window.clear();
            m_menu.draw(m_window);

        }
        else if (m_gameState == GameState::Playing) 
        {
            handleInputs(deltaTime);

            for (auto& player : m_players) 
            {
                player.MovePlayer(m_level, deltaTime);
            }

            m_bulletManager.update(m_level, deltaTime);
            m_powerUpManager.Update(m_level.getBricks());

            m_window.clear();

            m_level.drawBackground(m_window);
            m_bulletManager.draw(m_window);

            for (auto& player : m_players)
            {
                m_window.draw(player);
            }

            m_window.draw(m_level);
            m_powerUpManager.Draw(m_window);
        }

        m_window.display();
    }
}
