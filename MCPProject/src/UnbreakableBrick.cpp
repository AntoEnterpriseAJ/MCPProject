// UnbreakableBrick.cpp
#include "UnbreakableBrick.h"

UnbreakableBrick::UnbreakableBrick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : Brick(pos, texture, false, size)
{
}

void UnbreakableBrick::hit()
{
    // Nu se întâmplã nimic deoarece cãrãmida este indestructibilã.
}

bool UnbreakableBrick::isDestroyed() const
{
    return false; // Niciodatã nu este distrusã.
}
