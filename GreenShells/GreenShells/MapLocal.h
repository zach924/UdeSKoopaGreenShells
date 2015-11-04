#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
    MapLocal();
    ~MapLocal();
    Map* Clone();

    virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
    virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition);
	virtual bool CreateUnit(int unitType, Position pos, int owner);
	virtual bool CreateDistrict(int districtType, Position pos, int owner);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};