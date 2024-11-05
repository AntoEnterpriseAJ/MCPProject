#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, const sf::Texture& texture, Direction dir, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_state{State::Active}, m_direction{dir}
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

    if (dir == Direction::UP)
        m_sprite.setRotation(0.0f);
    else if (dir == Direction::DOWN)
        m_sprite.setRotation(180.0f);
    else if (dir == Direction::LEFT)
        m_sprite.setRotation(270.0f);
    else if (dir == Direction::RIGHT)
        m_sprite.setRotation(90.0f);
}

void Bullet::update()
{
    // TODO: maybe try using the velocity from GameObject, instead of kBulletSpeed
    if (m_direction == Direction::UP)
        m_sprite.move(0, -kBulletSpeed);
    else if (m_direction == Direction::DOWN)
        m_sprite.move(0, kBulletSpeed);
    else if (m_direction == Direction::LEFT)
        m_sprite.move(-kBulletSpeed, 0);
    else if (m_direction == Direction::RIGHT)
        m_sprite.move(kBulletSpeed, 0);

    // TODO: fix hardcoded values, maybe in the Game class?
    if (m_sprite.getPosition().x < 0 || m_sprite.getPosition().x > 1200.0f ||
        m_sprite.getPosition().y < 0 || m_sprite.getPosition().y > 900.0f)
    {
        m_state = State::Inactive;
    }
}

void Bullet::setState(Bullet::State state)
{
    m_state = state;
}

Bullet::State Bullet::getState() const
{
    return m_state;
}

