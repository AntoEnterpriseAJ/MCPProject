#pragma once
#include "PowerUpEffect.h"
#include <string>
#include <chrono>

class PowerUp {
public:
    PowerUp(PowerUpEffect effect, float duration);
    virtual ~PowerUp() = default;

    float GetDuration() const;
    PowerUpEffect GetEffect() const;

    void Activate();
    bool HasExpired() const;

protected:
    PowerUpEffect m_effect;
    float m_duration;

    std::chrono::steady_clock::time_point m_activationTime;
};
