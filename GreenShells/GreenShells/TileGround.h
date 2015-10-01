#pragma once
#include "Tile.h"
class TileGround : 
	public Tile
{
public:
	static const int TILE_TYPE = 0;

	TileGround(Position position);
	~TileGround();

	virtual bool CanTraverse();
	
	virtual boost::property_tree::ptree Serialize();
	static TileGround* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

