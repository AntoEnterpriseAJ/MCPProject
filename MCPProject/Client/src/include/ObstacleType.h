#pragma once
#include <string>

enum class ObstacleType
{
    None             = 0,
    Brick            = 1,
    UnbreakableBrick = 2,
    Bush             = 3,
    BombBrick        = 4,
};

inline std::string toString(ObstacleType obstacleType)
{
    switch (obstacleType)
    {
    case ObstacleType::None:
        return "none";
    case ObstacleType::Brick:
        return "brick";
    case ObstacleType::UnbreakableBrick:
        return "unbreakableBrick";
    case ObstacleType::Bush:
        return "bush";
    case ObstacleType::BombBrick:
        return "bombBrick";
    default:
        return "not a valid obstacle type";
    }
}