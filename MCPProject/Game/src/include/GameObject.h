#pragma once
#include "SFML/Graphics.hpp"
#include <string>


class GameObject : public sf::Drawable
{
public:
	GameObject() = default;

	GameObject(
		sf::Vector2f       pos, 
		const sf::Texture& texture, 
		sf::Vector2f       size,
		sf::Vector2f       vel = { 0.0f, 0.0f }
	);

	~GameObject() override = default;

	void SetPosition(sf::Vector2f pos);
	void SetSize    (sf::Vector2f size);
	void SetVelocity(sf::Vector2f vel);
	void SetTexture (const sf::Texture& texture);

	bool IsInArea(
		const sf::Vector2f& upLeft,
		const sf::Vector2f& downRight
	);

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