#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Level.h"

int main()
{
    const float baseWidth = 900.0f;
    const float baseHeight = 600.0f;

    // Window initialization
    sf::RenderWindow window(sf::VideoMode(baseWidth, baseHeight), "Player Shoot Example", sf::Style::Close);
    window.setFramerateLimit(100); // Limit FPS

    sf::View view = window.getDefaultView();

    // Create Player
    sf::RectangleShape playerShape(sf::Vector2f(50.0f, 50.0f)); // Dim player
    Player player(playerShape);
    player.setColor(sf::Color::Cyan);

    Level level;
    level.loadResources();

    // Game
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Shoot => Space
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                player.shoot();
            }
        }

        // Move player
        player.movePlayer(event);
        player.updateBullets();

        window.clear();

        window.draw(level);
        window.draw(player.getPlayerShape());

        

        // Draw bullet
        for (const auto& bullet : player.getBullets())
        {
            sf::RectangleShape bulletShape(sf::Vector2f(5.0f, 5.0f)); // Dim bullet
            bulletShape.setPosition(bullet.getX(), bullet.getY());
            bulletShape.setFillColor(sf::Color::Red);
            window.draw(bulletShape);
        }

        window.display();
    }

    return 0;
}
