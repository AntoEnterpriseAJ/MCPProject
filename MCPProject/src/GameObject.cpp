#include "GameObject.h"


GameObject::GameObject(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f vel)
	: m_position(pos), m_velocity(vel), m_texture(texture)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void GameObject::setSize(sf::Vector2f size)
{
	m_sprite.setScale(size.x / m_texture.getSize().x, size.y / m_texture.getSize().y);
}

void GameObject::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void GameObject::setTexture(const sf::Texture& texture)
{
	m_texture = texture;
	m_sprite.setTexture(m_texture);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Vector2f GameObject::getVelocity() const
{
	return m_velocity;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
