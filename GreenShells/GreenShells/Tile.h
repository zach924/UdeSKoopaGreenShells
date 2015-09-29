#pragma once
#include "Position.h"

class District;
class Unit;
class Player;

class Tile
{
	District* m_district;
	Unit* m_unit;
	int m_owner;

public:
	Position m_position;
	Tile(Position position);
	Tile();
	~Tile();

	District* GetDistrict();
	void SetDistrict(District* district);

	Unit* GetUnit();
	void SetUnit(Unit* unit);

	int GetPlayerOwnerID();
	void SetPlayerOwnerID(int id);

	virtual bool CanTraverse()=0;
};

