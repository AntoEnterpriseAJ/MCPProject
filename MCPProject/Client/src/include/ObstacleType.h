#pragma once
#include <string>

enum class ObstacleType
{
    None             = 0,
    Brick            = 1,
    Bush             = 2,
    UnbreakableBrick = 3,
    BombBrick        = 4,
};

inline std::string toString(ObstacleType obstacleType)
{
    switch (obstacleType)
    {
    case ObstacleType::None:             return "none";             break;
    case ObstacleType::Brick:            return "brick";            break;
    case ObstacleType::UnbreakableBrick: return "unbreakableBrick"; break;
    case ObstacleType::Bush:             return "bush";             break;
    case ObstacleType::BombBrick:        return "bombBrick";        break;
    default: return "not a valid obstacle type"; break;
    }
}