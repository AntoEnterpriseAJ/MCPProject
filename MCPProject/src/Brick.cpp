#include "Brick.h"

Brick::Brick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size) // Apelează constructorul clasei de bază
{
}

bool Brick::hit() {
    health--; // Scade sănătatea
    return health <= 0; // Returnează true dacă brick-ul nu mai există
}

int Brick::getSize() {
    return m_brickSize; // Returnează dimensiunea brick-ului
}

sf::FloatRect Brick::getBounds() const {
    return getSprite().getGlobalBounds(); // Returnează limitele brick-ului
}

bool Brick::operator==(const Brick& other) const {
    return this == &other; // Compară adresele pentru a verifica egalitatea
}
