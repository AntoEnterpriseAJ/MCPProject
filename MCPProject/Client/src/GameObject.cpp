#include "GameObject.h"

GameObject::GameObject(
    const sf::Vector2f& pos,
    const sf::Texture& texture,
    const sf::Vector2f& size,
    const sf::Vector2f& vel
)
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

void GameObject::setPosition(const sf::Vector2f& pos)
{
	m_sprite.setPosition(pos);
}

void GameObject::setSize(const sf::Vector2f& size)
{
	m_sprite.setScale(size.x / m_sprite.getTexture()->getSize().x, size.y / m_sprite.getTexture()->getSize().y);
}

void GameObject::setVelocity(const sf::Vector2f& vel)
{
	m_velocity = vel;
}

void GameObject::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

sf::FloatRect GameObject::getBounds() const noexcept
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f GameObject::getPosition() const noexcept
{
	return m_sprite.getPosition();
}

sf::Vector2f GameObject::getSize() const noexcept
{
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
    return {bounds.width, bounds.height};
}

sf::Vector2f GameObject::getVelocity() const noexcept
{
	return m_velocity;
}

sf::Sprite GameObject::getSprite() const noexcept
{
	return m_sprite;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}