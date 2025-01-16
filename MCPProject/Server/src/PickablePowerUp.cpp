#include "PickablePowerUp.h"

PickablePowerUp::PickablePowerUp(
    const Vec2f&  position,
    const Vec2f&  size,
    PowerUpEffect effect,
    float         duration
)
    : PowerUp{effect, duration}, GameObject{position, size}, m_isCollected{false}
{}

void PickablePowerUp::Collect()
{
    m_isCollected = true;
}

bool PickablePowerUp::IsCollected() const
{
    return m_isCollected;
}
