#include "Unit.h"
#include "GameSession.h"

Unit::Unit(int& ownerID)
	:Actor(ownerID)
{
}

Unit::~Unit()
{
}

void Unit::NotifyNewTurn()
{
	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
	// TODO: Update all player ressources
}

int Unit::GetPlayerOwnerID()
{
	return m_playerOwner;
}

void Unit::SetPlayerOwnerID(int id)
{
	m_playerOwner = id;
}