#include "PowerUpManager.h"
#include "ResourceManager.h"

void PowerUpManager::draw(sf::RenderWindow& window) const
{
    for (const auto& powerUp : m_powerUps)
    {
        window.draw(powerUp);
    }
}

std::vector<PowerUp>& PowerUpManager::getPowerUps()
{
    return m_powerUps;
}

void PowerUpManager::addPowerUp(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    PowerUpEffect effect
)
{
    ResourceManager& instance = ResourceManager::getInstance();

    switch (effect)
    {
    case PowerUpEffect::SpeedUp:
        m_powerUps.emplace_back(position, instance.getTexture("bombBrick"), size, effect);
        break;
    case PowerUpEffect::HealthUp:
        m_powerUps.emplace_back(position, instance.getTexture("bombBrick"), size, effect);
        break;
    }

}

void PowerUpManager::clearPowerUps()
{
    m_powerUps.clear();
}
