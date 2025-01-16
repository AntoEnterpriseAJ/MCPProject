#include "BuyablePowerUp.h"

BuyablePowerUp::BuyablePowerUp(PowerUpEffect effect, float duration, uint16_t cost)
    : PowerUp{ effect, duration }, m_cost{ cost }
{
}

uint16_t BuyablePowerUp::GetCost() const
{
    return 0;
}

