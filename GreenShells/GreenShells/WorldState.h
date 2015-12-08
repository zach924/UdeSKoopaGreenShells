#pragma once
#include <vector>
#include <set>
#include <mutex>
#include <memory>
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class Player;
class Map;

class WorldState
{
    std::recursive_mutex m_mutex;
    int m_turn;
    std::vector<std::shared_ptr<Player> > m_players;
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
    std::shared_ptr<Player> GetPlayer(int playerID);
    //Returns a copy of a player for drawing
    std::shared_ptr<Player> GetPlayerCopy(int playerID);

    std::vector<std::shared_ptr<Player> > GetPlayersCopy();

    std::vector<std::shared_ptr<Player> > GetPlayers();

    void PrepareLocalGame();
    int GetCurrentTurn();
    void NotifyNewTurn();

    int AddPlayer(std::string playerName);
    void RemovePlayer(int id);

    std::set<Position> MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    std::set<Position> Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    std::set<Position> CreateUnit(int unitType, Position pos, int owner);
    std::set<Position> CreateDistrict(int districtType, Position pos, int owner);
    bool SellUnit(Position pos, int ownerId);
    bool SellDistrict(Position pos, int ownerId);
    std::set<Position> UpgradeUnit(Position pos, int ownerId);
    std::set<Position> UpgradeDistrict(Position pos, int ownerId);
    bool HealUnit(Position pos, int ownerId);
    bool RepairDistrict(Position pos, int ownerId);

    bool AreAllPlayerReady();
    boost::property_tree::ptree Serialize();
    void Deserialize(boost::property_tree::ptree worldStateXml, int playerID);
    void DeserializePlayer(boost::property_tree::ptree playerXml, int playerID);
    void DeserializeTile(boost::property_tree::ptree playerXml, int playerID);
};
