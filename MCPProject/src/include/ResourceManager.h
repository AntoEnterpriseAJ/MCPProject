#pragma once
#include <SFML/Graphics.hpp>
#include <string_view>
#include <unordered_map>

class ResourceManager
{
public:
    static ResourceManager& getInstace();

    void loadTextureFromFile(std::string_view path, std::string_view name);
    const sf::Texture& getTexture(std::string_view name) const;

private:
    struct StringViewHash
    {
        std::size_t operator()(std::string_view str) const
        {
            return std::hash<std::string_view>{}(str);
        };
    };
private:
    ResourceManager() = default;
    std::unordered_map<std::string_view, sf::Texture> m_textures;
};
