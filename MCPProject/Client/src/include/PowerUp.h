#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include "PowerUpEffect.h"

class PowerUp : public GameObject
{
public:
    PowerUp(
        const sf::Vector2f& position,
        const sf::Texture&  texture,
        const sf::Vector2f& size,
        PowerUpEffect powerUpEffect
    );
private:
    PowerUpEffect m_powerUpEffect;
};