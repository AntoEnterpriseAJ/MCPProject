#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::getInstace()
{
    static ResourceManager resourceManager;
    return resourceManager;
}

void ResourceManager::loadTextureFromFile(std::string_view path, std::string_view name)
{
    if (m_textures.find(name) != m_textures.end())
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
    if (m_textures.find(name) == m_textures.end())
    {
        std::cerr << "WARNING::ResourceManager::getTexture: texture " << name << " not found" << std::endl;
        exit(-1);
    }

    return m_textures.at(name);
}
