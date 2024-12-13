#include "Game.h"
#include "ResourceManager.h"
#include "Explosion.h"

#include <iostream>

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"),
    m_level{},
    m_menu{ kWindowWidth, kWindowHeight },
    m_gameState{ GameState::Menu }
{
    ResourceManager& instance = ResourceManager::getInstance();
    instance.loadTextureFromFile("res/textures/penguin1.png", "player");
    instance.loadTextureFromFile("res/textures/albedo.png", "brick");
    instance.loadTextureFromFile("res/textures/ice.png", "bullet");
    instance.loadTextureFromFile("res/textures/bush.png", "bush");
    instance.loadTextureFromFile("res/textures/unbreakable.png", "unbreakableBrick");
    instance.loadTextureFromFile("res/textures/background.png", "background");
    instance.loadTextureFromFile("res/textures/explosionSheet.png", "explosionSheet");
    instance.loadTextureFromFile("res/textures/bombBrick.png", "bombBrick");
    instance.loadMusicFromFile("res/sfx/playershootexample.m_sfx.wav", m_backgroundMusic);
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
                if (player.canShoot())
                {
                    Direction dir = player.getDirection();
                    sf::Vector2f offset{ 0.0f, 0.0f };
                    float bulletOffsetDistance = 20.0f;

                    switch (player.getDirection())
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
                        player.getPosition() + offset,
                        ResourceManager::getInstance().getTexture("bullet"),
                        player.getDirection()
                    );

                    m_bulletManager.addBullet(std::move(bullet));

                    player.restartCooldown();
                }

            }
        }
    }

    for (auto& player : m_players)
    {
        player.update(deltaTime);
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

void Game::drawGrid()
{
    constexpr int cellSize = 40;

    for (int i = 0; i < kWindowWidth; i += cellSize)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i, 0)),
            sf::Vertex(sf::Vector2f(i, kWindowHeight))
        };

        m_window.draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < kWindowHeight; i += cellSize)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i)),
            sf::Vertex(sf::Vector2f(kWindowWidth, i))
        };

        m_window.draw(line, 2, sf::Lines);
    }
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
            }

            m_menu.handleInput(m_window);

            if (m_menu.isStartGameSelected())
            {
                m_gameState = GameState::Playing;
            }

            m_window.clear();
            m_menu.draw(m_window);
            m_window.display();
        }
        else if (m_gameState == GameState::Playing)
        {
            handleInputs(deltaTime);

            for (auto& player : m_players)
            {
                player.movePlayer(m_level, deltaTime);
            }

            m_bulletManager.update(m_level, deltaTime);

            m_window.clear();

            m_level.drawBackground(m_window);
            m_bulletManager.draw(m_window);

            for (auto& player : m_players)
            {
                m_window.draw(player);
            }

            m_window.draw(m_level);
            // drawGrid(); // Uncomment for debugging

            m_window.display();
        }
    }
}