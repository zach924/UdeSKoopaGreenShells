#include "District.h"


District::District()
{
}

District::~District()
{
}

int District::GetPlayerOwnerID()
{
	return m_playerOwner;
}

void District::SetPlayerOwnerID(int ID)
{
	m_playerOwner = ID;
}
