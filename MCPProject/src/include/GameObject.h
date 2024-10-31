#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class GameObject : public sf::Drawable
{
public:
	GameObject() {}
	GameObject(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f vel = {0.0f, 0.0f});
	virtual ~GameObject() = default;

	void setPosition(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setVelocity(sf::Vector2f vel);
	void setTexture(const sf::Texture& texture);

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize()	   const; // TODO: implement
	sf::Vector2f getVelocity() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Vector2f m_velocity;
	sf::Sprite	 m_sprite;
};