#include "GameObject.h"

GameObject::GameObject(const Vec2f& position, const Vec2f& size)
    : m_size{size}, m_origin{0.0f, 0.0f}, m_position{position}
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

// TODO: implement
void GameObject::rotate(float)
{

}

void GameObject::setOrigin(const Vec2f& originOffset)
{
    m_origin = originOffset;
}

void GameObject::setPosition(const Vec2f& position)
{
    m_position = position;
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
    return m_position - m_origin;
}

Vec2f GameObject::getBottomRight() const noexcept
{
    return m_position - m_origin + m_size;
}
