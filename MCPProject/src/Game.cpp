#include "Game.h"
#include "ResourceManager.h"

Game::Game(uint16_t windowWidth, uint16_t windowHeight)
    : m_window(sf::VideoMode(windowWidth, windowHeight), "Test"), m_level{}
{
    ResourceManager& instance = ResourceManager::getInstace();

    instance.loadTextureFromFile("res/plane.png", "player");
    instance.loadTextureFromFile("res/albedo.png", "brick");
    instance.loadTextureFromFile("res/missile.png", "bullet");

    m_player = Player(sf::Vector2f{ 100.0f, 80.0f }, ResourceManager::getInstace().getTexture("player"), sf::Vector2f{ 50.0f, 50.0f });
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
            m_player.shoot(ResourceManager::getInstace().getTexture("bullet"));
        }
    }

    m_player.movePlayer(m_level.getBricks());
    m_player.updateBullets(m_level.getBricks());
}

void Game::render()
{
    while (m_window.isOpen())
    {
        handleInputs();

        m_window.clear();

        for (auto& bullet : m_player.getBullets())
        {
            m_window.draw(bullet);
        }

        m_window.draw(m_level);
        m_window.draw(m_player);

        m_window.display();
    }
}


