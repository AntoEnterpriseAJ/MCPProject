#include "Bullet.h"

Bullet::Bullet(const Vec2f& pos, Direction dir, const Vec2f& size, uint16_t damage)
    : GameObject{ pos, size }, m_state{ State::Active }
    , m_direction{ dir }, m_damage{ damage }, m_playerID{}
{
    setOrigin(size / 2.0f);

    switch (dir)
    {
    case Direction::Up:
        this->rotate(0);
        break;
    case Direction::Down:
        this->rotate(180);
        break;
    case Direction::Left:
        this->rotate(270);
        break;
    case Direction::Right:
        this->rotate(90);
        break;
    }
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

bool Bullet::isActive() const noexcept
{
    return m_state == State::Active;
}

Direction Bullet::getDirection() const noexcept
{
    return m_direction;
}

Bullet::State Bullet::getState() const noexcept
{
    return m_state;
}

uint16_t Bullet::getDamage() const noexcept
{
    return m_damage;
}

uint8_t Bullet::getPlayerID() const noexcept
{
    return m_playerID;
}

