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
	Player secPlayer = Player();
	Player thirdPlayer = Player();
	Player fourthPlayer = Player();
	AddPlayer(firstPlayer);
	AddPlayer(secPlayer);
	AddPlayer(thirdPlayer);
	AddPlayer(fourthPlayer);
	RemovePlayer(thirdPlayer.GetPlayerID());
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}

void WorldState::RemovePlayer(int id)
{
	auto IsPlayerDifferent = [&](Player player) { return id == player.GetPlayerID(); };
	std::remove_if(m_players.begin(), m_players.end(), IsPlayerDifferent);
	int i = 0;
	i++;
}
