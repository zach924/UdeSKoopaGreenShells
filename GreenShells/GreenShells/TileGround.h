#pragma once
#include "Tile.h"
class TileGround :
	public Tile
{
public:
	static Texture m_texture;
	TileGround(Position position);
	~TileGround();
};

