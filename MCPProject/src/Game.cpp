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
        sf::Vector2f{ 39.5f, 39.5f }
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
                Direction dir = m_player.getDirection();
                sf::Vector2f offset{ 0.0f, 0.0f };
                float bulletOffsetDistance = 20.0f;

                switch (m_player.getDirection())
                {
                case Direction::UP:
                    offset.y = -bulletOffsetDistance;
                    break;
                case Direction::DOWN:
                    offset.y = bulletOffsetDistance;
                    break;
                case Direction::LEFT:
                    offset.x = -bulletOffsetDistance;
                    break;
                case Direction::RIGHT:
                    offset.x = bulletOffsetDistance;
                    break;
                }

                Bullet bullet{
                    m_player.getPosition() + offset,
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

        handleInputs();
        m_bulletManager.update(m_level.getBricks(), deltaTime);

        m_window.clear();

        // Desenăm mai întâi bullet-urile (sub player)
        m_bulletManager.draw(m_window);

        // Desenăm player-ul (peste bullet-uri)
        m_window.draw(m_player);

        // Desenăm bush-ul (peste player)
        m_window.draw(m_level);

        drawGrid(); // debug purpose

        m_window.display();
    }
}
