#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GameObject.h"
#include "Player.h"
#include <fstream>
#include "Level.h"

static constexpr uint32_t initialWindowWidth = 800;
static constexpr uint32_t initialWindowHeight = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(initialWindowWidth, initialWindowHeight), "SFML test");

    Level level;
    level.loadResources();

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            player.movePlayer(event);
        }


        window.clear(sf::Color(255, 100, 100, 255));
        
		float currentTime = clock.getElapsedTime().asSeconds();

        window.draw(level);

        window.display();
    }

    return 0;
}