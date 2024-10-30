#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <cstdint>
#include "Player.h"

static constexpr uint32_t initialWindowWidth = 800;
static constexpr uint32_t initialWindowHeight = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(initialWindowWidth, initialWindowHeight), "SFML test");

	sf::Texture texture;
	texture.loadFromFile("res/albedo.png");

	GameObject gameObject({ initialWindowWidth / 2.0f, initialWindowHeight / 2.0f }, texture, { 0.0f, 0.0f });
	gameObject.setSize({ 100.0f, 100.0f });

	constexpr float circleRadius = 100.0f;
    sf::CircleShape circle(circleRadius);
	circle.setPosition(initialWindowWidth / 2.0f - circleRadius, initialWindowHeight / 2.0f - circleRadius);
    circle.setFillColor(sf::Color::Blue);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 100, 100, 255));
        
		float currentTime = clock.getElapsedTime().asSeconds();
        circle.setPosition(circle.getPosition().x + cos(currentTime) * 0.01
                          , circle.getPosition().y + sin(currentTime) * 0.01);

        window.draw(circle);
		window.draw(gameObject);

        window.display();
    }

    return 0;
}