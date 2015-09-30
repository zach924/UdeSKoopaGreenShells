#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
	MapLocal();
	~MapLocal();

	virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation);
};