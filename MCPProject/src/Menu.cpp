#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) 
{
    if (!backgroundTexture.loadFromFile("res/textures/background_menu.png")) 
    {
        std::cerr << "Nu s-a putut incarca imaginea de fundal!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(width) / backgroundTexture.getSize().x,
        static_cast<float>(height) / backgroundTexture.getSize().y
    );

    if (!font.loadFromFile("res/Jaro/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Nu s-a putut incarca font-ul!" << std::endl;
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
    window.draw(backgroundSprite);

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
