#pragma once
#include "GameObject.h"
#include <string>

class PowerUp : public GameObject
{
public:
    PowerUp(
        sf::Vector2f pos,
        const sf::Texture& texture,
        std::string powerUpName,
        sf::Vector2f size = { 20.f, 20.f },
        sf::Vector2f velocity = { 0.f, 0.f }
    )
        : GameObject(pos, texture, size, velocity),
        m_powerUpName(std::move(powerUpName))
    {}

    const std::string& GetPowerUpName() const { return m_powerUpName; }

private:
    std::string m_powerUpName;
};
