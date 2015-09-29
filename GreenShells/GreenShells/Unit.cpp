#include "Unit.h"


Unit::Unit()
{
}

Unit::~Unit()
{
}

int Unit::GetPlayerOwnerID()
{
	return m_playerOwner;
}

void Unit::SetPlayerOwnerID(int id)
{
	m_playerOwner = id;
}