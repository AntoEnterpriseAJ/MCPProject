#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string_view>
#include <unordered_map>
#include "ObstacleType.h"

class ResourceManager
{
public:
    static ResourceManager& getInstance();

    void loadTextureFromFile(std::string_view path, std::string_view name);

    [[nodiscard]] const sf::Texture& getTexture(std::string_view name) const;
    [[nodiscard]] const sf::Texture& getTexture(ObstacleType obstacleType) const;

    void loadMusicFromFile(std::string_view path, sf::Music& music);

private:
    ResourceManager() = default;

private:
    std::unordered_map<std::string_view, sf::Texture> m_textures;
};
