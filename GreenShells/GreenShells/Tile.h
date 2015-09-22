#pragma once
#include "Position.h"

class District;
class Unit;
class Player;

class Tile
{
	District* m_district;
	Unit* m_unit;
	Player* m_owner;

public:
	Position m_position;
	Tile(Position position);
	Tile();
	~Tile();

	void NotifyNewTurn();
};

