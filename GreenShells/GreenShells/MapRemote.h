#pragma once

#include "Map.h"
#include "RPCBase.h"



class MapRemote : public Map, public RPCBase
{
public:
	MapRemote();
	~MapRemote();
	Map* Clone();

	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
	virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};