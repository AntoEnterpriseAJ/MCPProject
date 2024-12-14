#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string_view>
#include <unordered_map>
#include <memory>

class ResourceManager
{
public:
    static ResourceManager& getInstance();

    void loadTextureFromFile(std::string_view path, std::string_view name);
    [[nodiscard]] const sf::Texture& getTexture(std::string_view name) const;

    void loadMusicFromFile(std::string_view path, sf::Music& music);
    static void loadSoundFromFile(std::string_view path, sf::SoundBuffer& buffer, sf::Sound& sound);

private:
    ResourceManager() = default;

private:
    std::unordered_map<std::string_view, sf::Texture> m_textures;
};
