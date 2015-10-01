#pragma once
#include "Tile.h"
class TileWater :
	public Tile<TileWater>
{

public:
	typedef Tile<TileWater> tBase;
	void LoadTexture();
	TileWater(Position position);
	~TileWater();
};

