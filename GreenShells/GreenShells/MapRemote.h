#pragma once

#include "Map.h"
#include "RPCBase.h"



class MapRemote : public Map, public RPCBase
{
public:
	MapRemote();
	~MapRemote();

	bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);

    static MapRemote* Deserialize(boost::property_tree::ptree mapNode);
};