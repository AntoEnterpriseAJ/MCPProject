module Level;

import <iostream>;
import <ranges>;
import "Brick.h";
import "Bush.h";
import "BombBrick.h";
import "ResourceManager.h";
import "Obstacle.h";


Level::Level()
    : m_ID{0}, m_levelLayout{}
{}

void Level::init()
{
    loadBackground();
}

void Level::update(const std::array<uint16_t, kHeight * kWidth>& updatedLevel)
{
    std::ranges::for_each(std::views::iota(0, static_cast<int>(kHeight)), [&](int i) {
        std::ranges::for_each(std::views::iota(0, static_cast<int>(kWidth)), [&](int j) {
            ObstacleType textureType{static_cast<ObstacleType>(updatedLevel[i * kWidth + j])};

            auto& current{(*this)[{i, j}]};
            if (current)
            {
                if (textureType == ObstacleType::None)
                {
                    current.reset();
                    return;
                }

                current->SetTexture(ResourceManager::getInstance().getTexture(textureType));
                return;
            }

            sf::Vector2f position{j * Obstacle::kObstacleSize, i * Obstacle::kObstacleSize};

            auto obstacle = createObstacle(textureType, position);
            if (!obstacle) return;

            (*this)[{i, j}] = std::move(obstacle);
        });
    });
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::ranges::for_each(m_levelLayout, [&target](const auto& obj){
        if (!obj) return;

        target.draw(*obj);
    });
}

void Level::drawBackground(sf::RenderWindow& window) const
{
    window.draw(m_background);
}

uint8_t Level::getID() const noexcept
{
    return m_ID;
}

std::unique_ptr<Obstacle>& Level::operator[](const Position& position)
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}

const std::unique_ptr<Obstacle>& Level::operator[](const Position& position) const
{
    auto [posY, posX] = position;
    return m_levelLayout[posY * kWidth + posX];
}

void Level::loadBackground()
{
    m_background.setTexture(ResourceManager::getInstance().getTexture("background"));
    m_background.setPosition(sf::Vector2{ 0.0f, 0.0f });
}

std::unique_ptr<Obstacle> Level::createObstacle(ObstacleType obstacleType, const sf::Vector2f& position)
{
    if (obstacleType == ObstacleType::None)
    {
        return {nullptr};
    }
    else if (obstacleType == ObstacleType::Brick)
    {
        return std::make_unique<Brick>(position, ResourceManager::getInstance().getTexture(obstacleType));
    }
    else if (obstacleType == ObstacleType::BombBrick)
    {
        return std::make_unique<BombBrick>(position, ResourceManager::getInstance().getTexture(obstacleType));
    }
    else if (obstacleType  == ObstacleType::Bush)
    {
        return std::make_unique<Bush>(position, ResourceManager::getInstance().getTexture(obstacleType));
    }
    else if (obstacleType  == ObstacleType::UnbreakableBrick)
    {
        return std::make_unique<Brick>(position, ResourceManager::getInstance().getTexture(obstacleType));
    }
    else
    {
        std::cerr << std::format("Error! Invalid obstacle type: {}\n", toString(obstacleType));
    }
}

Level::levelLayout& Level::getBricks()
{
    return m_levelLayout;
}

const Level::levelLayout& Level::getBricks() const
{
    return m_levelLayout;
}