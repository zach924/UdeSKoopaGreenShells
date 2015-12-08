#pragma once

#include "Map.h"
#include "RPCBase.h"

class Player;

class MapRemote : public Map, public RPCBase
{
public:
    MapRemote();
    ~MapRemote();
    Map* Clone();

    void VisionChange(std::shared_ptr<Player> player);

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
    virtual void RemoveFogOfWarForPlayer(int playerID);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};