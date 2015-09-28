#pragma once
#include "Tile.h"
class TileMountain :
	public Tile
{
public:
	TileMountain(Position position);
	~TileMountain();

    virtual boost::property_tree::ptree Serialize();
};

