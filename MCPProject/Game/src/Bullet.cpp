#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(sf::Vector2f pos, const sf::Texture& texture, Direction dir, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_state{State::Active}, m_direction{dir}
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

    if (dir == Direction::Up)
        m_sprite.setRotation(0.0f);
    else if (dir == Direction::Down)
        m_sprite.setRotation(180.0f);
    else if (dir == Direction::Left)
        m_sprite.setRotation(270.0f);
    else if (dir == Direction::Right)
        m_sprite.setRotation(90.0f);
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
    m_sprite.move(offsetX, offsetY);
}

Direction Bullet::getDirection() const
{
    return m_direction;
}

Bullet::State Bullet::getState() const
{
    return m_state;
}

