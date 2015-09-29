#include "Actor.h"

Actor::Actor(int ownerID,Position position)
	:m_position(position),
  m_ownerID(ownerID)
{
}


Actor::~Actor()
{
}
