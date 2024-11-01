#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include "Level.h"

int main()
{
    const float baseWidth = 900.0f;
    const float baseHeight = 600.0f;

    sf::RenderWindow window(sf::VideoMode(baseWidth, baseHeight), "Player Shoot Example", sf::Style::Close);
    window.setFramerateLimit(100); // Limit FPS

    sf::View view = window.getDefaultView();

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("res/plane.png"))
    {
        std::cerr << "ERROR: Unable to load player texture!" << std::endl;
        return -1;
    }

    Player player(playerTexture);

    Level level;
    level.loadResources();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Shoot => SPACE
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                player.shoot();
            }
        }

        player.movePlayer();
        player.updateBullets();

        window.clear();

        window.draw(level);
        player.draw(window);

        for (const auto& bullet : player.getBullets())
        {
            sf::RectangleShape bulletShape(sf::Vector2f(5.0f, 5.0f));
            bulletShape.setPosition(bullet.getX(), bullet.getY());
            bulletShape.setFillColor(sf::Color::Red);
            window.draw(bulletShape);
        }

        window.display();
    }

    return 0;
}
