#pragma once
#include <nlohmann/json.hpp>

enum class PowerUpEffect
{
    SpeedUp,
    HealthUp,
    DamageUp,
    ReduceShootCooldown,
    BulletSpeedUp,
    Count
};

NLOHMANN_JSON_SERIALIZE_ENUM(PowerUpEffect, {
    {PowerUpEffect::SpeedUp, "speed_up"},
    {PowerUpEffect::HealthUp, "health_up"},
    {PowerUpEffect::DamageUp, "damage_up"},
    {PowerUpEffect::ReduceShootCooldown, "reduce_shoot_cooldown"},
    {PowerUpEffect::BulletSpeedUp, "bullet_speed_up"}
})