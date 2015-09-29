#include "TileGround.h"


TileGround::TileGround(Position position)
:Tile(position)
{
}


TileGround::~TileGround()
{
}

bool TileGround::CanTraverse()
{
	//TODO : Add abilities that allows water
	return true;
}