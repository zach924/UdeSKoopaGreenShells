#include "Actor.h"

Actor::Actor(Player& owner)
	:m_position(-1,-1),
	m_owner(owner)
{
}


Actor::~Actor()
{
}
