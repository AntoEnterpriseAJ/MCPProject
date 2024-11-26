#pragma once
#include "GameObject.h"

class Menu {
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window);

    bool isStartGame() const;

private:
    sf::Font font;      
    sf::Text startButton;   
    sf::Text exitButton;  
    bool startGame = false;   
};