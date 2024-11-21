#include "BrickManager.h"

void BrickManager::destroyBlocksInArea(std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& bricks,
    float area, const sf::Vector2f& position)
{
    for (int index = 0; index < bricks.size(); ++index)
    {
        if (std::holds_alternative<Brick>(bricks[index]))
        {
            Brick& brick = std::get<Brick>(bricks[index]);
            if (brick.isInArea(
                sf::Vector2f(position.x - area, position.y + area),
                sf::Vector2f(position.x + area, position.y - area)))
            {
                bricks.erase(bricks.begin() + index);
                index--;
            }
        }
    }
}
