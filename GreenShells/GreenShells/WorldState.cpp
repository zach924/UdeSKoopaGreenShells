#include <algorithm>

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

void WorldState::PrepareGame()
{
	Player firstPlayer = Player();
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
