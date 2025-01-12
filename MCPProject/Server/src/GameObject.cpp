#include "GameObject.h"
#include <cmath>

GameObject::GameObject(const Vec2f& position, const Vec2f& size)
    : m_size{size}, m_origin{0.0f, 0.0f}, m_position{position}, m_rotation{0}
{}

bool GameObject::collides(const GameObject& other) const noexcept
{
    Vec2f topLeft{this->getTopLeft()};
    Vec2f bottomRight{this->getBottomRight()};
    Vec2f otherTopLeft{other.getTopLeft()};
    Vec2f otherBottomRight{other.getBottomRight()};

    bool xCollision = otherBottomRight.x >= topLeft.x &&
                      otherTopLeft.x <= bottomRight.x;

    bool yCollision = otherBottomRight.y >= topLeft.y &&
                      otherTopLeft.y <= bottomRight.y;

    return xCollision && yCollision;
}

bool GameObject::collides(const Vec2f& otherTopLeft, const Vec2f& otherBottomRight) const noexcept
{
    Vec2f topLeft{this->getTopLeft()};
    Vec2f bottomRight{this->getBottomRight()};

    bool xCollision = otherBottomRight.x >= topLeft.x &&
                      otherTopLeft.x <= bottomRight.x;

    bool yCollision = otherBottomRight.y >= topLeft.y &&
                      otherTopLeft.y <= bottomRight.y;

    return xCollision && yCollision;
}

void GameObject::setOrigin(const Vec2f& originOffset)
{
    m_origin = originOffset;
}

void GameObject::setPosition(const Vec2f& position)
{
    m_position = position;
}

void GameObject::setSize(const Vec2f& size)
{
    m_size = size;
}

Vec2f GameObject::getOrigin() const noexcept
{
    return m_origin;
}

Vec2f GameObject::getPosition() const noexcept
{
    return m_position;
}

Vec2f GameObject::getSize() const noexcept
{
    return m_size;
}

Vec2f GameObject::getTopLeft() const noexcept
{
    return m_position - m_origin;
}

Vec2f GameObject::getBottomRight() const noexcept
{
    return m_position - m_origin + m_size;
}
