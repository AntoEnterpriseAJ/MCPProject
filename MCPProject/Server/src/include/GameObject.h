#pragma once
#include <Vec2f.h>

class GameObject
{
public:
    GameObject(const Vec2f& position, const Vec2f& size);
    virtual ~GameObject() = default;

    bool collides(const GameObject& other) const noexcept;
    bool collides(const Vec2f& otherTopLeft, const Vec2f& otherBottomRight) const noexcept;

    void rotate(int angle);
    void setOrigin(const Vec2f& originOffset);
    void setPosition(const Vec2f& position);
    void setSize(const Vec2f& size);

    Vec2f getOrigin() const noexcept;
    Vec2f GetPosition() const noexcept;
    Vec2f GetSize() const noexcept;
    Vec2f getTopLeft() const noexcept;
    Vec2f getBottomRight() const noexcept;

private:
    Vec2f getEffectiveSize() const noexcept;
    Vec2f getRotatedOrigin() const noexcept;

    Vec2f m_position;
    Vec2f m_origin;  
    Vec2f m_size;    
    int   m_rotation;
};