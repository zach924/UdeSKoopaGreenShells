#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
    MapLocal();
    ~MapLocal();
    Map* Clone();

    std::set<Position> DiscoverArea(Position pos, int range, int playerId);
    void RemoveFogOfWarForPlayer(int playerID);

    virtual std::set<Position> MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    virtual std::set<Position> Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    virtual std::set<Position> CreateUnit(int unitType, Position pos, int owner, bool upgrade);
    virtual std::set<Position> CreateDistrict(int districtType, Position pos, int owner, bool upgrade);
    virtual bool SellDistrict(Position pos, int owner);
    virtual bool SellUnit(Position pos, int owner);
    virtual std::set<Position> UpgradeUnit(Position pos, int owner);
    virtual std::set<Position> UpgradeDistrict(Position pos, int owner);
    virtual bool HealUnit(Position pos, int owner);
    virtual bool RepairDistrict(Position pos, int owner);

    void ShareVision(int playerOne, int playerTwo);
    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};