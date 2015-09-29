#pragma once
#include "Tile.h"
class TileGround :
	public Tile<TileGround>
{
public:
	typedef Tile<TileGround> tBase;
	void LoadTexture();
	TileGround(Position position);
	~TileGround();
};

