#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class GameObject : public sf::Drawable
{
public:
	GameObject() = default;
	GameObject(
		const sf::Vector2f& pos, 
		const sf::Texture&  texture, 
		const sf::Vector2f& size, 
		const sf::Vector2f& vel = { 0.0f, 0.0f }
	);

	~GameObject() override = default;

	void setPosition(const sf::Vector2f& pos);
	void setSize    (const sf::Vector2f& size);
	void setVelocity(const sf::Vector2f& vel);
	void setTexture (const sf::Texture& texture);

	sf::FloatRect getBounds()   const noexcept;
	sf::Vector2f  getPosition() const noexcept;
	sf::Vector2f  getSize()	    const noexcept;
	sf::Vector2f  getVelocity() const noexcept;
	sf::Sprite    getSprite()   const noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Vector2f m_velocity;
	sf::Sprite	 m_sprite;
};