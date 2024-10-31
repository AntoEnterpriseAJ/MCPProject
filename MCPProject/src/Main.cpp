#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"

int main()
{
    // Window initialization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Player Shoot Example");
    window.setFramerateLimit(100); // Limit FPS

    // Create Player
    sf::RectangleShape playerShape(sf::Vector2f(50.0f, 50.0f)); // Dim player
    Player player(playerShape);
    player.setColor(sf::Color::Cyan);

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
