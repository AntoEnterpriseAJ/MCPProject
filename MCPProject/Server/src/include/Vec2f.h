#pragma once
#include <functional>

struct Vec2f
{
    float x;
    float y;

    friend constexpr Vec2f operator+(const Vec2f& lhs, const Vec2f& rhs) noexcept
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    friend constexpr Vec2f operator-(const Vec2f& lhs, const Vec2f& rhs) noexcept
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    friend constexpr Vec2f operator/(const Vec2f& lhs, float scalar) noexcept
    {
        return {lhs.x / scalar, lhs.y / scalar};
    }

    friend constexpr Vec2f operator*(const Vec2f& rhs, float scalar) noexcept
    {
        return { rhs.x * scalar, rhs.y * scalar };
    }

    friend constexpr Vec2f operator*(float scalar, const Vec2f& vec) noexcept 
    {
        return { vec.x * scalar, vec.y * scalar };
    }

    constexpr Vec2f operator-() const noexcept
    {
        return {-x, -y};
    }

    constexpr std::pair<int, int> toGridCoords(float gridSize) const noexcept
    {
        return {
            static_cast<int>(std::floor(x / gridSize)),
            static_cast<int>(std::floor(y / gridSize))
        };
    }
};