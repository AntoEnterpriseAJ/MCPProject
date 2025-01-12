#pragma once
#include <array>
#include "Obstacle.h"
#include "ObstacleType.h"
#include <vector>
#include <memory>

class Level
{
public:
    static constexpr uint16_t kWidth    { 30 };
    static constexpr uint16_t kHeight   { 20 };
    static constexpr float    kGridSize { 40.0f };
public:
    using Position = std::pair<uint16_t, uint16_t>;
    using levelLayout = std::array<std::unique_ptr<Obstacle>, kHeight* kWidth>;
    using layoutTypes = std::array<uint16_t, kHeight * kWidth>;
public:
    Level();

    void load();
    void updateLayoutTypes(); // TODO: maybe update ONLY when it's necessary, fine for now

    uint8_t getID() const noexcept;
    const layoutTypes& getLayoutTypes() const noexcept; 
    layoutTypes& getLayoutTypes();
    const levelLayout& getLayout() const noexcept;
    levelLayout& getLayout();

    void setObstacle(const Position& position, std::unique_ptr<Obstacle>& obstacle, ObstacleType obstacleType);

    std::unique_ptr<Obstacle>& operator[](const Position& position);
    const std::unique_ptr<Obstacle>& operator[](const Position& position) const;
private:
    std::unique_ptr<Obstacle> createObstacle(ObstacleType obstacleType, const Vec2f& position);
private:
    uint8_t m_ID;
    levelLayout m_levelLayout;
    layoutTypes m_layoutTypes;
};