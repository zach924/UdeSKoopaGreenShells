#pragma once
#include "Tile.h"
class TileWater :
	public Tile
{
public:
	static Texture m_texture;
	TileWater(Position position);
	~TileWater();
};

