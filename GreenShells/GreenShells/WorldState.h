#pragma once
#include <vector>
#include "Map.h"
#include "Ptree_ForwardDeclaration.h"

class Player;


class WorldState
{
	std::vector<Player> m_players;
	
	Map m_map;
public:
	WorldState();
	~WorldState();

	void PrepareGame();

	void AddPlayer(const Player& player);

	void RemovePlayer(int id);

    Map GetMap();

    boost::property_tree::ptree Serialize();
    static WorldState Deserialize(boost::property_tree::ptree worldStateXml);
};

