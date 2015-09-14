#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"

Tile::Tile()
: m_district(nullptr), m_unit(nullptr), m_owner(nullptr)
{
}


Tile::~Tile()
{
}
