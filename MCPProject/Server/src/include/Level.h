#pragma once
#include <array>

class Level
{
public:
    static constexpr uint16_t kWidth{ 30 };
    static constexpr uint16_t kHeight{ 20 };
    using Position = std::pair<uint16_t, uint16_t>;
    using levelLayout = std::array<uint16_t, kHeight * kWidth>;
public:
    void load();

    uint8_t getID() const noexcept;

    const levelLayout& getLayout() const noexcept;

    uint16_t& operator[](const Position& position);
    const uint16_t& operator[](const Position& position) const;
private:
    uint8_t m_ID;
    levelLayout m_levelLayout;
};