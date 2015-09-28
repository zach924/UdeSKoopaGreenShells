#pragma once
#include "Tile.h"
class TileMountain :
	public Tile
{
public:
	static Texture m_texture;
	TileMountain(Position position);
	~TileMountain();
};

