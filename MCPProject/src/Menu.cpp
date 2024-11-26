#include "Menu.h"

Menu::Menu(float width, float height) 
{
    if (!font.loadFromFile("res/Jaro/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        // ERROR
    }

    startButton.setFont(font);
    startButton.setCharacterSize(50);
    startButton.setString("Start Game");
    startButton.setPosition(width / 2 - startButton.getLocalBounds().width / 2, height / 2 - 100);

    exitButton.setFont(font);
    exitButton.setCharacterSize(50);
    exitButton.setString("Exit");
    exitButton.setPosition(width / 2 - exitButton.getLocalBounds().width / 2, height / 2 + 50);
}

void Menu::draw(sf::RenderWindow& window) 
{
    window.draw(startButton);
    window.draw(exitButton);
}

void Menu::handleInput(sf::RenderWindow& window) 
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        startGame = true;
    }

    if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        window.close();
    }
}

bool Menu::isStartGame() const 
{
    return startGame;
}
