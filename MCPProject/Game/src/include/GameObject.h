#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ResourceManager.h"
#include <string>
#include <list>

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

	void setPosition(sf::Vector2f pos);
	void setSize    (sf::Vector2f size);
	void setVelocity(sf::Vector2f vel);
	void setTexture (const sf::Texture& texture);

	bool isInArea(
		const sf::Vector2f& upLeft,
		const sf::Vector2f& downRight
	);

	sf::FloatRect getBounds()   const noexcept;
	sf::Vector2f  getPosition() const noexcept;
	sf::Vector2f  getSize()	    const noexcept;
	sf::Vector2f  getVelocity() const noexcept;
	sf::Sprite    getSprite()   const noexcept;

	static void playSound(std::string_view path);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::Vector2f m_velocity;
	sf::Sprite	 m_sprite;
	static std::list<sf::Sound> m_activeSounds;

};