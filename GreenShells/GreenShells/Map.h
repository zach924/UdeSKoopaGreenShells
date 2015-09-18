#include "Position.h"
#pragma once
#include <vector>
#include "Tile.h"

class Map
{
	static const int ROWS = 64;
	static const int COLUMNS = 64;

	std::vector<std::vector<Tile>> m_tiles;

public:
	Map();
	~Map();

	void GenerateTiles();

	void GetArea(Position position, int distance);

	Tile GetTile(Position);
};

