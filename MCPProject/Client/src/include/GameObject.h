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
	void SetTexture (const sf::Texture& texture);

	sf::FloatRect GetBounds()   const noexcept;
	sf::Vector2f  GetPosition() const noexcept;
	sf::Vector2f  GetSize()	    const noexcept;
	sf::Vector2f  GetVelocity() const noexcept;
	sf::Sprite    GetSprite()   const noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Vector2f m_velocity;
	sf::Sprite	 m_sprite;
};