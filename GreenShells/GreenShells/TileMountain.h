#pragma once
#include "Tile.h"
class TileMountain :
	public Tile
{
public:
	TileMountain(Position position);
	~TileMountain();

	virtual bool CanTraverse();
	
	virtual boost::property_tree::ptree Serialize();
	static TileMountain* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

