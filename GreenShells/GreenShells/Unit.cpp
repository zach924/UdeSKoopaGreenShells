#include "Unit.h"
#include "GameSession.h"

Unit::Unit(int& ownerID, int attackRange)
	:Actor(ownerID),
	m_attackRange(attackRange)
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