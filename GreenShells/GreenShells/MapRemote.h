#pragma once

#include "Map.h"
#include "RPCBase.h"


class MapRemote : public Map, public RPCBase
{
public:
	MapRemote();
	~MapRemote();

	bool MoveUnit(int id, Position unitLocation, Position newLocation);
};