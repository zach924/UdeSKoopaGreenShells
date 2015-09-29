#include "Actor.h"

Actor::Actor(int ownerID,Position position)
	:m_position(position),
  m_ownerID(ownerID)
{
}


Actor::~Actor()
{
}

void Actor::SetOwnerID(int ID)
{
	m_ownerID = ID;
}

int Actor::GetOwnerID()
{
	return m_ownerID;
}
