#pragma once

#include "Map.h"
#include "RPCBase.h"

class MapRemote : public Map, public RPCBase
{
public:
    MapRemote();
    ~MapRemote();
    Map* Clone();

    void VisionChange(int playerId);

    virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
    virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition);
    virtual bool CreateUnit(int unitType, Position pos, int owner);
    virtual bool CreateDistrict(int districtType, Position pos, int owner);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};