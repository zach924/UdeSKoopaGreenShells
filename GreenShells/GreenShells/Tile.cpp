#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"

Tile::Tile(Position position)
: m_district(nullptr), m_unit(nullptr), m_owner(-1), m_position(position)
{
}

Tile::Tile()
:m_position(-1,-1)
{
}


Tile::~Tile()
{
}

District* Tile::GetDistrict()
{
	return m_district;
}
void Tile::SetDistrict(District* district)
{
	m_district = district;
}

Unit * Tile::GetUnit()
{
	return m_unit;
}
void Tile::SetUnit(Unit* unit)
{
	m_unit = unit;
}

int Tile::GetPlayerOwnerID()
{
	return m_owner;
}
void Tile::SetPlayerOwnerID(int id)
{
	m_owner = id;
}