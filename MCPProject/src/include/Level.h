#pragma once
#include "Brick.h"
#include "Bush.h"

#include <vector>
#include <variant>

using LevelObject = std::variant<Brick, Bush>;

static std::vector<LevelObject> m_levelLayout;

class Level : public sf::Drawable
{
public:
    void loadResources();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static Brick& findBrick(float posX, float posY);
    static std::vector<std::variant<Brick, Bush>>& getBricks();

private:
    int m_levelWidth{ 30 };
    int m_levelHeight{ 20 };

    sf::Texture m_brickTexture;
    sf::Texture m_bushTexture;
};