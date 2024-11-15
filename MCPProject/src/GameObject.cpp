#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size, sf::Vector2f vel)
	: m_velocity(vel)
{
	if (texture.getSize().x == 0 || texture.getSize().y == 0)
	{
		throw std::invalid_argument("Invalid texture size");
	}

	m_sprite.setTexture(texture);
	m_sprite.setPosition(pos);
	setSize(size);
}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void GameObject::setSize(sf::Vector2f size)
{
	m_sprite.setScale(size.x / m_sprite.getTexture()->getSize().x, size.y / m_sprite.getTexture()->getSize().y);
}

void GameObject::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void GameObject::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

sf::Vector2f GameObject::getSize() const
{
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
    return {bounds.width, bounds.height};
}

sf::Vector2f GameObject::getVelocity() const
{
	return m_velocity;
}

sf::Sprite GameObject::getSprite() const
{
	return m_sprite;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}