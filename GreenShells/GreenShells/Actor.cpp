#include "Actor.h"

Actor::Actor(int ownerID,Position position)
	:m_position(position),
    m_ownerID(ownerID),
    m_foodCost(0),
    m_scienceCost(0),
    m_weaponCost(0),
    m_foodRatioBonus(0.0),
    m_scienceRatioBonus(0.0),
    m_weaponRatioBonus(0.0)
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
