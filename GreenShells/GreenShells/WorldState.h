#pragma once
#include <vector>
#include "Ptree_ForwardDeclaration.h"

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
  boost::property_tree::ptree Serialize();
  static WorldState Deserialize(boost::property_tree::ptree worldStateXml);
};

