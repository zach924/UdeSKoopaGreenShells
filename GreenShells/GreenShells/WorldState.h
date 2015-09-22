#pragma once
#include <vector>
#include "Map.h"

class Player;

class WorldState
{
	std::vector<Player> m_players;
	
	Map m_map;
public:
	WorldState();
	~WorldState();

	void PrepareGame();
	void NotifyNewTurn();

	void AddPlayer(const Player& player);

	void RemovePlayer(int id);

	bool IsAllPlayerReady();
};

