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
public:
    static constexpr uint16_t kDefaultDuration{ 10 };
    static constexpr uint16_t kDamageUpCost{ 200 };
    static constexpr uint16_t kReduceShootCooldownCost{ 500 };
    static constexpr uint16_t getCost(PowerUpEffect effect)
    {
        switch (effect)
        {
        case PowerUpEffect::DamageUp:
            return 200;
        case PowerUpEffect::ReduceShootCooldown:
            return 400;
        case PowerUpEffect::BulletSpeedUp:
            return 10;
        default:
            return 0;
        }
    }
protected:
    PowerUpEffect m_effect;
    float m_duration;

    std::chrono::steady_clock::time_point m_activationTime;
};
