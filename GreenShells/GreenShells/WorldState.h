#pragma once
#include <vector>

class Player;
class Map;

class WorldState
{
	std::vector<Player> m_players;	
	Map* m_map;

public:
	WorldState();
	~WorldState();

	void SetMap(Map* map);
	Map* GetMap();

	void PrepareGame();

	void AddPlayer(const Player& player);
	void RemovePlayer(int id);
};

