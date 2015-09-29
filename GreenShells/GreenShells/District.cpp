#include "District.h"
#include "GameSession.h"

District::District(int& ownerID)
	:Actor(ownerID)
{
}

District::~District()
{
}

void District::NotifyNewTurn()
{
	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
	// TODO: Update all player ressources
}

int District::GetPlayerOwnerID()
{
	return m_playerOwner;
}

void District::SetPlayerOwnerID(int ID)
{
	m_playerOwner = ID;
}
