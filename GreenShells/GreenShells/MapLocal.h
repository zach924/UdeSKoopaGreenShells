#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
	MapLocal();
	~MapLocal();

	virtual bool MoveUnit(int id, Position unitLocation, Position newLocation);
};