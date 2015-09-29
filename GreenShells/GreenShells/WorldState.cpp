#include <algorithm>

#include "WorldState.h"
#include "Player.h"
#include "MapLocal.h"

WorldState::WorldState()
:m_map(nullptr), m_players()
{
	
}

WorldState::~WorldState()
{
}

void WorldState::SetMap(Map* map)
{
	m_map = map;
}

Map* WorldState::GetMap()
{
	return m_map;
}

void WorldState::PrepareGame()
{
	m_map =	new MapLocal();
	m_map->GenerateTiles();
	AddPlayer(Player());
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}
void WorldState::RemovePlayer(int id)
{
	for (Player &player : m_players)
	{
		if (player.GetPlayerID() == id)
		{
			player.SetPlayerDead();
			break;
		}
	}
}
