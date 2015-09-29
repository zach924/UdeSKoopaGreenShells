#pragma once
#include <vector>

class Player;
class Map;

class WorldState
{
	int m_turn;
	std::vector<Player> m_players;	
	Map* m_map;

public:
	WorldState();
	~WorldState();

	void SetMap(Map* map);
	Map* GetMap();

	void PrepareGame();
	int GetCurrentTurn();
	void NotifyNewTurn();

	void AddPlayer(const Player& player);
	void RemovePlayer(int id);
	Player& GetPlayer(int playerID);

	bool AreAllPlayerReady();
};

