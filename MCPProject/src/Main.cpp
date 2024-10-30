#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"

static constexpr uint32_t initialWindowWidth = 800;
static constexpr uint32_t initialWindowHeight = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(initialWindowWidth, initialWindowHeight), "SFML test");

    Player player(sf::RectangleShape(sf::Vector2f(60, 60)));

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        player.movePlayer(event);

        window.draw(player.getPlayerShape());
        
		float currentTime = clock.getElapsedTime().asSeconds();

        window.display();
    }

    return 0;
}