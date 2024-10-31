#include "Bullet.h"

Bullet::Bullet(int x, int y, Direction dir, float speed)
    : m_direction(dir), m_speed(speed), m_active(true)
{
    m_shape.setSize(sf::Vector2f(10.0f, 10.0f));
    m_shape.setPosition(x, y);
}

void Bullet::update()
{
    // Direction bullet
    switch (m_direction)
    {
    case Direction::UP:
        m_shape.move(0, -m_speed);
        break;
    case Direction::DOWN:
        m_shape.move(0, m_speed);
        break;
    case Direction::LEFT:
        m_shape.move(-m_speed, 0);
        break;
    case Direction::RIGHT:
        m_shape.move(m_speed, 0);
        break;
    }

    // Verify bullet
    if (m_shape.getPosition().y < 0 || m_shape.getPosition().y > 600 ||
        m_shape.getPosition().x < 0 || m_shape.getPosition().x > 800)
    {
        m_active = false;
    }
}

bool Bullet::getIsActive() const
{
    return m_active;
}

int Bullet::getX() const
{
    return m_shape.getPosition().x;
}

int Bullet::getY() const
{
    return m_shape.getPosition().y;
}
