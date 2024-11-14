#include "Game.h"
#include "ResourceManager.h"

Game::Game()
    : m_window(sf::VideoMode(kWindowWidth, kWindowHeight), "Test"), m_level{}
{
    ResourceManager& instance = ResourceManager::getInstance();

    instance.loadTextureFromFile("res/plane.png", "player");
    instance.loadTextureFromFile("res/albedo.png", "brick");
    instance.loadTextureFromFile("res/missile.png", "bullet");

    m_player = Player(
        sf::Vector2f{ 100.0f, 80.0f }, 
        ResourceManager::getInstance().getTexture("player"), 
        sf::Vector2f{ 50.0f, 50.0f }
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
            if (m_player.canShoot())
            {
                Bullet bullet{
                    m_player.getPosition(),
                    ResourceManager::getInstance().getTexture("bullet"),
                    m_player.getDirection()
                };

                m_bulletManager.addBullet(bullet);
                m_player.restartTimer();
            }
        }
    }

    m_player.movePlayer(Level::getBricks());
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
    constexpr int cellSize = 25;

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
        handleInputs();
        m_bulletManager.update(m_level.getBricks());

        m_window.clear();

        m_window.draw(m_level);
        m_window.draw(m_player);
        m_bulletManager.draw(m_window);

        drawGrid(); // debug purpose

        m_window.display();
    }
}
