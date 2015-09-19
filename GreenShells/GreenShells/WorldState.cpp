#include "WorldState.h"
#include "Player.h"

//FOR REVIEW ONLY
//#include <iostream>

WorldState::WorldState()
:m_map(), m_players()
{
	m_map.GenerateTiles();

	//FOR REVIEW ONLY
	/*auto area = m_map.GetArea(Position(6, 10), 2);
	for (int i = 0; i < area.size(); ++i)
	{
		std::cout << area[i].m_position.ToString();
	}

	auto area1 = m_map.GetArea(Position(1, 63), 3);
	for (int i = 0; i < area1.size(); ++i)
	{
		std::cout << area1[i].m_position.ToString();
	}*/
}

WorldState::~WorldState()
{
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}
