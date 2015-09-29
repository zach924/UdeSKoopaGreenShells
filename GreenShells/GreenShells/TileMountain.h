#pragma once
#include "Tile.h"
class TileMountain :
	public Tile<TileMountain>
{

public:
	typedef Tile<TileMountain> tBase;
	void LoadTexture();
	TileMountain(Position position);
	~TileMountain();
};

