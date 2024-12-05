#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!backgroundTexture.loadFromFile("res/textures/background_menu.png"))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(width) / backgroundTexture.getSize().x,
        static_cast<float>(height) / backgroundTexture.getSize().y
    );

    if (!font.loadFromFile("res/font_text/Jaro-Regular-VariableFont_opsz.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
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

void Menu::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundSprite);
    window.draw(startButton);
    window.draw(exitButton);
}

void Menu::handleInput(sf::RenderWindow& window)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    if (startButton.getGlobalBounds().contains(mousePos) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        startGameSelected = true;
    }

    if (exitButton.getGlobalBounds().contains(mousePos) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window.close();
    }
}


bool Menu::isStartGameSelected() const
{
    return startGameSelected;
}