#pragma once
#include "PowerUp.h"

class BuyablePowerUp : public PowerUp {
public:
    BuyablePowerUp(PowerUpEffect effect, float duration, uint16_t cost);

    uint16_t GetCost() const;

private:
    uint16_t m_cost;
};
