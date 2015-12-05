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

    virtual std::vector<Position> MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    virtual std::vector<Position> Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    virtual bool CreateUnit(int unitType, Position pos, int owner, bool upgrade);
    virtual bool CreateDistrict(int districtType, Position pos, int owner, bool upgrade);
    virtual bool SellDistrict(Position pos, int owner);
    virtual bool SellUnit(Position pos, int owner);
    virtual bool UpgradeUnit(Position pos, int owner);
    virtual bool UpgradeDistrict(Position pos, int owner);
    virtual bool HealUnit(Position pos, int owner);
    virtual bool RepairDistrict(Position pos, int owner);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};