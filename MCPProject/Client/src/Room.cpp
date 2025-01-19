#include "Room.h"

Room::Room(int id, int connectedPlayers, const std::string& label, const sf::Vector2f& position, const sf::Vector2f& size)
	: m_id{id}
	, m_connectedPlayers{connectedPlayers}
	, m_button(label, position, size)
{
}

int Room::getID() const
{
	return m_id;
}

int Room::getConnectedPlayers() const
{
	return m_connectedPlayers;
}

Button Room::getButton() const
{
	return m_button;
}
