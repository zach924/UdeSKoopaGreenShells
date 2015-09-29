#include "Actor.h"
#include "GameSession.h"

Actor::Actor(int ownerID,Position position)
	:m_position(position),
  m_ownerID(ownerID)
{
}


Actor::~Actor()
{
}

void Actor::NotifyNewTurn()
{
	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
	// TODO: Update all player ressources
}
