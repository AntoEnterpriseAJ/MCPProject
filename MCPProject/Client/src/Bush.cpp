#include "Bush.h"

Bush::Bush(
    const sf::Vector2f& pos,
    const sf::Texture& texture
)
	: Obstacle(pos, texture, { kObstacleSize, kObstacleSize }, true, false)
{}