#pragma once

class Tile;

class Map
{
	static const int ROWS = 64;
	static const int COLUMNS = 64;

	Tile* m_tiles[ROWS][COLUMNS];

public:
	Map();
	~Map();

	void GenerateTiles();
};

