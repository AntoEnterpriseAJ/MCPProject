#pragma once
#include "Brick.h"

#include <vector>
#include <variant>

static std::vector<Brick> m_levelLayout;

class Level : public sf::Drawable
{
public:
    void loadResources();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static Brick& findBrick(float posX, float posY);
    static std::vector<Brick>& getBricks();

private:
    int m_levelWidth  { 30 };
    int m_levelHeight { 20 };

    sf::Texture m_brickTexture;
};