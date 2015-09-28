#pragma once
#include "Position.h"
#include "Texture.h"

class District;
class Unit;
class Player;

class Tile
{
	District* m_district;
	Unit* m_unit;
	Player* m_owner;

public:
	//static virtual Texture GetTexture()=0;
	Position m_position;
	Tile(Position position);
	Tile();
	~Tile();
};

