#include "Brick.h"

Brick::Brick(
    const sf::Vector2f& pos,
    const sf::Texture& texture,
    int health,
    bool passable,
    bool destroyable
)
    : Obstacle(pos, texture, { kObstacleSize, kObstacleSize }, passable, destroyable)
    , m_brickHealth(health)
{}

bool Brick::isDestroyed() const noexcept
{
    return m_brickHealth <= 0;
}

void Brick::hit()
{
    if (m_brickHealth > 0)
        --m_brickHealth;
}