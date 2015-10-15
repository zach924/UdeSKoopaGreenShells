#pragma once
#include <vector>
#include <mutex>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include "Ptree_ForwardDeclaration.h"
#include "Map.h"
#include "Player.h"

class WorldState
{
private:
	friend class boost::serialization::access;
	std::recursive_mutex m_mutex;
	int m_turn;
	std::vector<Player> m_players;
	Map* m_map;

	//Serialize
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_turn;
		ar & m_players;
		ar & m_map;
	}
public:
	WorldState();
	~WorldState();

	//Temp Hack
	Map* GetMap();
	//Returns a copy of the map for drawing
	Map GetMapCopy();

	void PrepareLocalGame();
	void PrepareRemoteGame();
	int GetCurrentTurn();
	void NotifyNewTurn();

	int AddPlayer(const Player& player);
	void RemovePlayer(int id);
	Player GetPlayer(int playerID);

	bool AreAllPlayerReady();
	boost::property_tree::ptree Serialize();
	void Deserialize(boost::property_tree::ptree worldStateXml);
};

