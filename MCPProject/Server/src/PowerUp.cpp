#include "PowerUp.h"
#include "PowerUp.h"
#include "PowerUp.h"

PowerUp::PowerUp(PowerUpEffect effect, float duration)
    : m_effect{ effect }, m_duration{ duration }
{}

float PowerUp::GetDuration() const
{
    return m_duration;
}

PowerUpEffect PowerUp::GetEffect() const
{
    return m_effect;
}

void PowerUp::Activate()
{
    m_activationTime = std::chrono::steady_clock::now();
}

bool PowerUp::HasExpired() const
{
    if (m_duration <= 0.0f) return false;
    return std::chrono::steady_clock::now() - m_activationTime > std::chrono::duration<float>(m_duration);
}
