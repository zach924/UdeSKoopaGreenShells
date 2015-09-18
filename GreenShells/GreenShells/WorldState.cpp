#include "WorldState.h"
#include "Tile.h"
#include "Player.h"

WorldState::WorldState()
	:m_tiles(), m_players()
{
	Player player;
	m_players.emplace_back(player);
}

WorldState::~WorldState()
{
}
