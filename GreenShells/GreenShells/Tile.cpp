#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"

Tile::Tile(Position position)
: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
{
}

Tile::Tile()
:m_position(-1,-1)
{
}


Tile::~Tile()
{
}

void Tile::NotifyNewTurn()
{
	if (m_district != nullptr)
	{
		m_district->NotifyNewTurn();
	}

	if (m_unit != nullptr)
	{
		m_unit->NotifyNewTurn();
	}
}
