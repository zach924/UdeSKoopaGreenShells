#pragma once
#include <vector>
#include <mutex>
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class Player;
class Map;

class WorldState
{
    std::recursive_mutex m_mutex;
    int m_turn;
    std::vector<Player*> m_players;
    Map* m_map;
    bool m_remote;
public:
    WorldState(bool isRemote);
    ~WorldState();

    //Temp Hack
    Map* GetMap();
    //Returns a copy of the map for drawing
    Map* GetMapCopy();
    //Temp Hack
    Player* GetPlayer(int playerID);
    //Returns a copy of a player for drawing
    Player* GetPlayerCopy(int playerID);

    void PrepareLocalGame();
    int GetCurrentTurn();
    void NotifyNewTurn();

    int AddPlayer(std::string playerName);
    void RemovePlayer(int id);

    bool AreAllPlayerReady();
    boost::property_tree::ptree Serialize();
    void Deserialize(boost::property_tree::ptree worldStateXml);
};
