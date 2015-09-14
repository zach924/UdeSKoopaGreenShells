#pragma once
#include <vector>

class Tile;
class Player;

class GameSession
{
	std::vector<Player> m_players;
	std::vector<Tile> m_tiles;
public:
	GameSession();
	~GameSession();
};

