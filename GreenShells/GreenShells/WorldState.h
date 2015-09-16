#pragma once

#include <vector>

class Tile;
class Player;

class WorldState
{
	std::vector<Player> m_players;
	std::vector<Tile> m_tiles;
public:
	WorldState();
	~WorldState();
};

