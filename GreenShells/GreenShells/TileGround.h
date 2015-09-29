#pragma once
#include "Tile.h"
class TileGround : 
	public Tile
{
public:
	TileGround(Position position);
	~TileGround();

    virtual boost::property_tree::ptree Serialize();
    TileGround Deserialize(boost::property_tree::ptree tileNode);
};

