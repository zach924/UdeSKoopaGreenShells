#pragma once
#include "Tile.h"
class TileWater :
	public Tile
{
public:
	TileWater(Position position);
	~TileWater();

    boost::property_tree::ptree Serialize();
};

