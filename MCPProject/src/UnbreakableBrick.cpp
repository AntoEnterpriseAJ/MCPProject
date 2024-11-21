// UnbreakableBrick.cpp
#include "UnbreakableBrick.h"

UnbreakableBrick::UnbreakableBrick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : Brick(pos, texture, false, size)
{
}

void UnbreakableBrick::hit()
{
    // Nu se �nt�mpl� nimic deoarece c�r�mida este indestructibil�.
}

bool UnbreakableBrick::isDestroyed() const
{
    return false; // Niciodat� nu este distrus�.
}
