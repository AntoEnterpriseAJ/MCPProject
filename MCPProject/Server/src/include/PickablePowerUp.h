#pragma once
#include "PowerUp.h"
#include "GameObject.h"
#include "Player.h"
#include "Vec2f.h"

class PickablePowerUp : public PowerUp, public GameObject
{
public:
    PickablePowerUp(
        const Vec2f&  position,
        const Vec2f&  size,
        PowerUpEffect effect,
        float         duration
    );
    virtual ~PickablePowerUp() override = default;

    void Collect();
    bool IsCollected() const;
public:
    static constexpr Vec2f kPowerUpSize = { 25.0f, 25.0f };
private:
    bool m_isCollected;
};
