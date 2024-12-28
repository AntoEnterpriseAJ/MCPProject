#pragma once
#include <Vec2f.h>

class GameObject
{
public:
    GameObject(const Vec2f& topLeft, const Vec2f& size);
    virtual ~GameObject() = default;

    bool collides(const GameObject& other) const noexcept;
    bool collides(const Vec2f& otherTopLeft, const Vec2f& otherBottomRight) const noexcept;

    // TODO: implement
    void rotate(float);
    void setOrigin(const Vec2f& originOffset);
    void setPosition(const Vec2f& position);

    Vec2f getOrigin()      const noexcept;
    Vec2f GetPosition()    const noexcept;
    Vec2f GetSize()        const noexcept;
    Vec2f getTopLeft()     const noexcept;
    Vec2f getBottomRight() const noexcept;
private:
    Vec2f m_position;
    Vec2f m_origin;
    Vec2f m_size;
};