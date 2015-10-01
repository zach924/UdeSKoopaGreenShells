#pragma once
#include "Position.h"
#include <vector>
#include "TileBase.h"
#include "Texture.h"

class Map
{
protected:
	static const int ROWS = 64;
	static const int COLUMNS = 64;

	std::vector<std::vector<TileBase*>> m_tiles;

public:
	Map();
	~Map();
	static Texture m_texture;

	void GenerateTiles();

	std::vector<TileBase*> GetArea(Position position, int distance);

	TileBase* GetTile(Position);
};

