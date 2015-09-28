#pragma once
#include "Tile.h"
class TileGround : 
	public Tile
{
public:
	TileGround(Position position);
	~TileGround();

    boost::property_tree::ptree Serialize();
};

