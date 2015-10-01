#pragma once
#include "Tile.h"
class TileWater :
	public Tile
{
public:
	TileWater(Position position);
	~TileWater();

    virtual boost::property_tree::ptree Serialize();
    static TileWater* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

