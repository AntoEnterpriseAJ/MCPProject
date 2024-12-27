#pragma once

struct Vec2f
{
    float x;
    float y;

    friend Vec2f operator+(const Vec2f& first, const Vec2f& second)
    {
        return {first.x + second.x, first.y + second.y};
    }

    friend Vec2f operator-(const Vec2f& first, const Vec2f& second)
    {
        return {first.x - second.x, first.y - second.y};
    }

    friend Vec2f operator/(const Vec2f& first, float scalar)
    {
        return {first.x / scalar, first.y / scalar};
    }
};