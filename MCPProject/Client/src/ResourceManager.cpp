#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager resourceManager;
    return resourceManager;
}

void ResourceManager::loadTextureFromFile(std::string_view path, std::string_view name)
{
    if (m_textures.contains(name))
    {
        std::cerr << "WARNING::ResourceManager::loadTexture: the texture was already loaded" << std::endl;
        return;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(path.data()))
    {
        std::cerr << "ERROR::ResourceManager::loadTexture: can't find file at " << path << std::endl;
        exit(-1);
    }

    m_textures[name] = texture;
}

const sf::Texture& ResourceManager::getTexture(std::string_view name) const
{
    if (!m_textures.contains(name))
    {
        std::cerr << "ERROR::ResourceManager::getTexture: texture " << name << " not found" << std::endl;
        exit(-1);
    }

    return m_textures.at(name);
}

const sf::Texture& ResourceManager::getTexture(ObstacleType obstacleType) const
{
    std::string textureName{toString(obstacleType)};
    if (!m_textures.contains(textureName))
    {
        std::cerr << "ERROR::ResourceManager::getTexture: texture " << textureName << " not found" << std::endl;
        exit(-1);
    }

    return m_textures.at(textureName); 
}

void ResourceManager::loadMusicFromFile(std::string_view path, sf::Music& music)
{
    if (!music.openFromFile(path.data()))
    {
        std::cerr << "ERROR::ResourceManager::loadMusic: Failed to load music file from " << path << std::endl;
        exit(-1);
    }
}
