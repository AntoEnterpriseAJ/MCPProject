#pragma once
#include <vector>
#include <variant>
#include "Brick.h"
#include "Bush.h"
#include "UnbreakableBrick.h"

class BrickManager
{
public:

	static void destroyBlocksInArea(std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& bricks, float area, const sf::Vector2f& position);
};