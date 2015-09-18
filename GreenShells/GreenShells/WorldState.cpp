#include "WorldState.h"
#include "Player.h"

WorldState::WorldState()
:m_map(), m_players()
{
	m_map.GenerateTiles();
}

WorldState::~WorldState()
{
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}
