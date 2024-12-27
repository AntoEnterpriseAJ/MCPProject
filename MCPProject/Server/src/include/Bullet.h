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
        const Vec2f& size = {kBulletSizeX, kBulletSizeY}
    );
    ~Bullet() override = default;

    void update(float deltaTime);
    void setState(State state);
    void move(float offsetX, float offsetY);

    Direction getDirection() const;
    State getState() const;

private:
    static constexpr float kBulletSpeed { 400.0f };
    static constexpr float kBulletSizeX { 20.0f };
    static constexpr float kBulletSizeY { 50.0f };
private:
    Direction m_direction : 2;
    State     m_state     : 1;
};