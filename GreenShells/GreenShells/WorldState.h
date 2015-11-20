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
    std::shared_ptr<Map> GetMapCopy();
    //Temp Hack
    Player* GetPlayer(int playerID);
    //Returns a copy of a player for drawing
    std::shared_ptr<Player> GetPlayerCopy(int playerID);

    std::vector<Player*> GetPlayersCopy();

    std::vector<Player*> GetPlayers();

    void PrepareLocalGame();
    int GetCurrentTurn();
    void NotifyNewTurn();

    int AddPlayer(std::string playerName);
    void RemovePlayer(int id);

    bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
    bool Attack(int ownerID, Position attackerPosition, Position targetPosition);
    bool CreateUnit(int unitType, Position pos, int owner);
    bool CreateDistrict(int districtType, Position pos, int owner);

    bool AreAllPlayerReady();
    boost::property_tree::ptree Serialize();
    void Deserialize(boost::property_tree::ptree worldStateXml);
};
