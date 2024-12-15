#pragma once
#include "Obstacle.h"
#include <vector>

class Level : public sf::Drawable
{
public:
    using Position = std::pair<uint16_t, uint16_t>;
public:
    void load();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void drawBackground(sf::RenderWindow& window) const;

    std::unique_ptr<Obstacle>& operator[](const Position& position);
    const std::unique_ptr<Obstacle>& operator[](const Position& position) const;

    std::vector<std::unique_ptr<Obstacle>>& getBricks();
    const std::vector<std::unique_ptr<Obstacle>>& getBricks() const;
private:
    void loadBackground();
private:
    static constexpr uint16_t kLevelWidth{ 30 };
    static constexpr uint16_t kLevelHeight{ 20 };
private:
    std::vector<std::unique_ptr<Obstacle>> m_levelLayout;
    sf::Sprite m_background;
};