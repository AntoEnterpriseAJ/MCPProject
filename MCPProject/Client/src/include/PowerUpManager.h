#pragma once
#include "PowerUp.h"

class PowerUpManager
{
public:
    void draw(sf::RenderWindow& window) const;

    void addPowerUp(
        const sf::Vector2f& position,
        const sf::Vector2f& size,
        PowerUpEffect effect
    );

    void clearPowerUps();
    std::vector<PowerUp>& getPowerUps();

private:
    std::vector<PowerUp> m_powerUps;
};
