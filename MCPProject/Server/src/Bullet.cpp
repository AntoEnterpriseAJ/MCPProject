#include "Bullet.h"

Bullet::Bullet(const Vec2f& pos, Direction dir, const Vec2f& size)
    : GameObject{ pos, size }, m_state{State::Active}, m_direction{dir}
{
    setOrigin(size / 2.0f);
}

void Bullet::update(float deltaTime)
{
    if (m_direction == Direction::Up)
        this->move(0, -kBulletSpeed * deltaTime);
    else if (m_direction == Direction::Down)
        this->move(0, kBulletSpeed * deltaTime);
    else if (m_direction == Direction::Left)
        this->move(-kBulletSpeed * deltaTime, 0);
    else if (m_direction == Direction::Right)
        this->move(kBulletSpeed * deltaTime, 0);
}

void Bullet::setState(Bullet::State state)
{
    m_state = state;
}

void Bullet::move(float offsetX, float offsetY)
{
    this->setPosition(this->GetPosition() + Vec2f{offsetX, offsetY});
}

bool Bullet::isActive() const
{
    return m_state == State::Active;
}

Direction Bullet::getDirection() const
{
    return m_direction;
}

Bullet::State Bullet::getState() const
{
    return m_state;
}

