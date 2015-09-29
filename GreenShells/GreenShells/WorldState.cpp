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
	AddPlayer(Player());
}

void WorldState::NotifyNewTurn()
{
	//Notify map of a new turn
	m_map.NotifyNewturn();

	//Notify players of a new turn
	for (Player& player : m_players)
	{
		if(player.IsAlive())
		{
			player.NotifyNewTurn();
		}
	}
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
			player.SetDead();
			break;
		}
	}
}

Map WorldState::GetMap()
{
	return m_map;
}

bool WorldState::IsAllPlayerReady()
{
	bool result = true;

	for (Player& player : m_players)
	{
		if (player.IsAlive())
		{
			result &= player.IsPlayerReadyForNextTurn();
		}
	}

	return result;
}
