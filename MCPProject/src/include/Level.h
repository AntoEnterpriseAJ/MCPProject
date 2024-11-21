#pragma once
#include "Brick.h"
#include "Bush.h"
#include "UnbreakableBrick.h"

#include <vector>
#include <variant>

using LevelObject = std::variant<Brick, Bush, UnbreakableBrick>;

class Level : public sf::Drawable
{
public:
    void loadResources();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Brick& findBrick(float posX, float posY);
    std::vector<LevelObject>& getBricks();
private:
    int m_levelWidth{ 30 };
    int m_levelHeight{ 20 };


    std::vector<LevelObject> m_levelLayout;

    sf::Texture m_brickTexture;
    sf::Texture m_bushTexture;
    sf::Texture m_unbreakableTexture;
};