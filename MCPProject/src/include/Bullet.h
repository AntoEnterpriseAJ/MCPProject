#pragma once
#include <SFML/Graphics.hpp>
#include "Direction.h"

class Bullet {
public:
    // Constructorul glonțului
    Bullet(int x, int y, Direction dir, float speed);

    // Metoda de actualizare a poziției glonțului
    void update();

    // Verifică dacă glonțul este activ
    bool getIsActive() const;

    // Obține coordonata X
    int getX() const;

    // Obține coordonata Y
    int getY() const;

private:
    sf::RectangleShape m_shape; // Forma glonțului
    Direction m_direction;      // Direcția glonțului
    float m_speed;              // Viteza glonțului
    bool m_active;              // Starea glonțului
};
