#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GameObject.h"
#include "Player.h"

static constexpr uint32_t initialWindowWidth = 800;
static constexpr uint32_t initialWindowHeight = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(initialWindowWidth, initialWindowHeight), "SFML test");

	sf::Texture texture;
	texture.loadFromFile("res/albedo.png");

    Player player({ initialWindowWidth / 2.0f, initialWindowHeight / 2.0f }, texture, { 0.0f, 0.0f });
    player.setSize({ 100.0f , 100.0f });
        
	
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

        window.draw(player);

        window.display();
    }

    return 0;
}