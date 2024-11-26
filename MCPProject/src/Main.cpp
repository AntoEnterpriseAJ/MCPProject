#include "Game.h"
#include "Menu.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Joc");

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menu.handleInput(window);

        window.clear();
        menu.draw(window);
        window.display();

        if (menu.isStartGame()) 
        {
            Game game;

            game.render();

            break;
        }
    }

    return 0;
}