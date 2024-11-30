#pragma once
#include "Brick.h"
#include "Bush.h"
#include "UnbreakableBrick.h"
#include "BombBrick.h"

#include <vector>
#include <variant>

using LevelObject = std::variant<std::monostate, Brick, Bush, UnbreakableBrick>;

class Level : public sf::Drawable
{
public:
    using Position = std::pair<uint16_t, uint16_t>;
public:
    void load();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void drawBackground(sf::RenderWindow& window) const;

    LevelObject& operator[](const Position& position);
    const LevelObject& operator[](const Position& position) const;

    std::vector<LevelObject>& getBricks();
    const std::vector<LevelObject>& getBricks() const;
private:
    void loadBackground();
private:
    static constexpr uint16_t kLevelWidth{ 30 };
    static constexpr uint16_t kLevelHeight{ 20 };
private:
    std::vector<LevelObject> m_levelLayout;
    sf::Sprite m_background;
};