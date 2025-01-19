#pragma once
#include "Direction.h"
#include "Vec2f.h"
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    enum class State : uint8_t
    {
        Active,
        Inactive,
    };
public:
    Bullet(
        const Vec2f& pos, 
        Direction    dir,
        uint8_t      playerID,
        const Vec2f& size = { kBulletSizeX, kBulletSizeY },
        uint16_t     damage = kBulletDamage,
        float        speed  = kBulletSpeed
    );
    ~Bullet() override = default;

    void update(float deltaTime);
    void setState(State state);
    void move(float offsetX, float offsetY);

    bool isActive() const noexcept;
    Direction getDirection() const noexcept;
    State getState() const noexcept;
    uint16_t getDamage() const noexcept;
    uint8_t getPlayerID() const noexcept;

public:
    static constexpr float    kBulletSpeed { 400.0f };
    static constexpr float    kBulletSizeX { 20.0f };
    static constexpr float    kBulletSizeY { 50.0f };
    static constexpr uint16_t kBulletDamage{ 25 };
private:
    uint16_t  m_damage;
    uint8_t   m_playerID;
    Direction m_direction : 2;
    State     m_state     : 1;
    float     m_speed;
};