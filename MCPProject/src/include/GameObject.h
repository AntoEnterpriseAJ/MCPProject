#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject(sf::Vector2f pos = {0.0f, 0.0f}, sf::Color color = sf::Color::Red
			  , sf::Vector2f size = {0.0f, 0.0f}, sf::Vector2f vel = {0.0f, 0.0f});
	virtual ~GameObject() = default;

	void setPosition(sf::Vector2f pos);
	void setColor(sf::Color color);
	void setSize(sf::Vector2f size);
	void setVelocity(sf::Vector2f vel);

	sf::Vector2f getPosition() const;
	sf::Color	 getColor()	   const;
	sf::Vector2f getSize()	   const;
	sf::Vector2f getVelocity() const;

protected:
	sf::Vector2f m_position;
	sf::Color    m_color;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
};