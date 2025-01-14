#include "GameObject.h"

GameObject::GameObject(const Vec2f& position, const Vec2f& size)
    : m_position{ position }, m_origin{ 0.0f, 0.0f }, m_size{ size }, m_rotation{ 0 }
{
}

bool GameObject::collides(const GameObject& other) const noexcept
{
    return collides(other.getTopLeft(), other.getBottomRight());
}

bool GameObject::collides(const Vec2f& otherTopLeft, const Vec2f& otherBottomRight) const noexcept
{
    Vec2f topLeft = this->getTopLeft();
    Vec2f bottomRight = this->getBottomRight();

    bool xCollision = otherBottomRight.x >= topLeft.x &&
        otherTopLeft.x <= bottomRight.x;

    bool yCollision = otherBottomRight.y >= topLeft.y &&
        otherTopLeft.y <= bottomRight.y;

    return xCollision && yCollision;
}

void GameObject::rotate(int angle)
{
    m_rotation = (m_rotation + angle) % 360;

    if (m_rotation < 0) {
        m_rotation += 360;
    }
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

Vec2f GameObject::GetPosition() const noexcept
{
    return m_position;
}

Vec2f GameObject::GetSize() const noexcept
{
    return m_size;
}

Vec2f GameObject::getTopLeft() const noexcept
{
    Vec2f rotatedOrigin = getRotatedOrigin();
    return m_position - rotatedOrigin;
}

Vec2f GameObject::getBottomRight() const noexcept
{
    return getTopLeft() + getEffectiveSize();
}

Vec2f GameObject::getEffectiveSize() const noexcept
{
    if (m_rotation % 180 == 0) {
        return m_size;
    }
    return { m_size.y, m_size.x };
}

Vec2f GameObject::getRotatedOrigin() const noexcept
{
    switch (m_rotation) {
    case 90:
        return { m_origin.y, m_size.x - m_origin.x };
    case 180:
        return { m_size.x - m_origin.x, m_size.y - m_origin.y };
    case 270:
        return { m_size.y - m_origin.y, m_origin.x };
    default:
        return m_origin;
    }
}