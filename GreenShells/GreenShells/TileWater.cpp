#include "TileWater.h"


TileWater::TileWater(Position position)
:Tile(position)
{
}


TileWater::~TileWater()
{
}

bool TileWater::CanTraverse()
{
	//TODO : Add abilities that allows water
	return false;
}