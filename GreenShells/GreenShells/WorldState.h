#pragma once
#include <vector>
#include "Map.h"

class Player;

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}

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
    //void Deserialize(boost::property_tree::ptree worldStateXml);
};

