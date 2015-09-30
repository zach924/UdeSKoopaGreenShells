#include "TileMountain.h"


TileMountain::TileMountain(Position position)
:Tile(position)
{
}


TileMountain::~TileMountain()
{
}

bool TileMountain::CanTraverse()
{
	return false;
}