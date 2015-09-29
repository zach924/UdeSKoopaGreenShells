#include "WorldState.h"
#include "Player.h"

WorldState::WorldState()
:m_map(new Map()), m_players()
{
	m_map->GenerateTiles();
}

WorldState::~WorldState()
{
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}

Map* WorldState::GetMap()
{
	return m_map;
}
