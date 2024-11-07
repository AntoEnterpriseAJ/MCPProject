#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class GameObject : public sf::Drawable
{
public:
	GameObject() = default;
	GameObject(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size, sf::Vector2f vel = { 0.0f, 0.0f });
	virtual ~GameObject() = default;

	void setPosition(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setVelocity(sf::Vector2f vel);
	void setTexture(const sf::Texture& texture);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize()	   const;
	sf::Vector2f getVelocity() const;

	sf::Sprite getSprite() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Vector2f m_velocity;
	sf::Sprite	 m_sprite;
};