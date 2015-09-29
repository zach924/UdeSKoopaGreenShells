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

void WorldState::NotifyNewTurn()
{
	//Notify map of a new turn
	m_map->NotifyNewturn();

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

Player & WorldState::GetPlayer(int playerID)
{
	return m_players.at(playerID);
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