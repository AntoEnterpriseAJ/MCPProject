#pragma once
#include <array>;
#include <memory>;
#include "ObstacleType.h";
#include "Obstacle.h";


class Level : public sf::Drawable
{
public:
    static constexpr uint16_t kWidth{ 30 };
    static constexpr uint16_t kHeight{ 20 };
    using Position = std::pair<uint16_t, uint16_t>;
    using levelLayout = std::array<std::unique_ptr<Obstacle>, kHeight* kWidth>;
public:
    Level();

    void init();
    void update(const std::array<uint16_t, kHeight* kWidth>& updatedLevel);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void drawBackground(sf::RenderWindow& window) const;

    uint8_t getID() const noexcept;

    std::unique_ptr<Obstacle>& operator[](const Position& position);
    const std::unique_ptr<Obstacle>& operator[](const Position& position) const;

    levelLayout& getBricks();
    const levelLayout& getBricks() const;
private:
    void loadBackground();
    std::unique_ptr<Obstacle> createObstacle(ObstacleType obstacleType, const sf::Vector2f& position);
private:
    uint8_t m_ID;
    levelLayout m_levelLayout;
    sf::Sprite  m_background;
};