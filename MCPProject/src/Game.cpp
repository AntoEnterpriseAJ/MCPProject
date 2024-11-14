#include "Game.h"
#include "ResourceManager.h"

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"), m_level{}
{
    ResourceManager& instance = ResourceManager::getInstance();

    instance.loadTextureFromFile("res/plane.png", "player");
    instance.loadTextureFromFile("res/albedo.png", "brick");
    instance.loadTextureFromFile("res/missile.png", "bullet");
    instance.loadTextureFromFile("res/bush.png", "bush");

    m_player = Player(
        sf::Vector2f{ 100.0f, 80.0f },
        ResourceManager::getInstance().getTexture("player"),
        sf::Vector2f{ 42.0f, 42.0f }
    );

    m_level.loadResources();
}

void Game::handleInputs()
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

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            m_player.shoot(ResourceManager::getInstance().getTexture("bullet"));
        }
    }

    m_player.movePlayer(Level::getBricks());
    m_player.updateBullets(Level::getBricks());
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
        handleInputs();
        m_player.updateTimer();
        m_window.clear();

        for (auto& bullet : m_player.getBullets())
        {
            m_window.draw(bullet);
        }

        m_window.draw(m_player);

        m_window.draw(m_level);

        m_window.display();
    }
}
