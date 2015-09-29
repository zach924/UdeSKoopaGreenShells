#pragma once
#include "Tile.h"
class TileWater :
	public Tile<TileWater>
{
	//static Texture m_texture;

public:
	typedef Tile<TileWater> tBase;
	void LoadTexture();
	TileWater(Position position);
	~TileWater();
};

