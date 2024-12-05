#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window) const;
    void handleInput(sf::RenderWindow& window);

    bool isStartGameSelected() const;

private:
    sf::Font font;
    sf::Text startButton;
    sf::Text exitButton;
    bool startGameSelected = false;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};