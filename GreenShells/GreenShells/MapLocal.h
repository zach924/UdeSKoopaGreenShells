#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
	MapLocal();
	~MapLocal();

	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
	virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};