#pragma once

#include <string>

#include <SFML/Graphics.hpp>
import Button;

class Room
{
public:
	Room(int id, int connectedPlayers, const std::string& label, const sf::Vector2f& position, const sf::Vector2f& size);

	int getID() const;
	int getConnectedPlayers() const;
	Button getButton() const;

private:
	int    m_id;
	int    m_connectedPlayers;
	Button m_button;
};