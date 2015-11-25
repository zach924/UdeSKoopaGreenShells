#pragma once
#include "Map.h"

class MapLocal : public Map
{
    int GetDistance(Position pos1, Position pos2);
public:
    MapLocal();
    ~MapLocal();
    Map* Clone();

    void DiscoverArea(Position pos, int range, int playerId);

    virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    virtual bool CreateUnit(int unitType, Position pos, int owner);
    virtual bool CreateDistrict(int districtType, Position pos, int owner);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};