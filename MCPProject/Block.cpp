#include "Block.h"

Block::Block(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject(pos, texture, size), health(3)
{
}

sf::FloatRect Block::getBounds() const
{
    return getSprite().getGlobalBounds();
}
