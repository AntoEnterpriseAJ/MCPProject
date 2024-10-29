#include "GameObject.h"

GameObject::GameObject(sf::Vector2f pos, sf::Color color, sf::Vector2f size, sf::Vector2f vel)
	: m_position(pos), m_color(color), m_size(size), m_velocity(vel)
{}

void GameObject::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void GameObject::setColor(sf::Color color)
{
	m_color = color;
}

void GameObject::setSize(sf::Vector2f size)
{
	m_size = size;
}

void GameObject::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Color GameObject::getColor() const
{
	return m_color;
}

sf::Vector2f GameObject::getSize() const
{
	return m_size;
}

sf::Vector2f GameObject::getVelocity() const
{
	return m_velocity;
}
