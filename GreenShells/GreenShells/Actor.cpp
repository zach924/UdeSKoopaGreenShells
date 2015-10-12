#include "Actor.h"

#include <iostream>

Actor::Actor(int ownerID,Position position)
	:m_position(position),
    m_ownerID(ownerID),
    m_foodCost(0),
    m_scienceCost(0),
    m_weaponCost(0),
    m_foodRatioBonus(0.0),
    m_scienceRatioBonus(0.0),
    m_weaponRatioBonus(0.0),
	m_health(100),
	m_attackDamage(0)
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

int Actor::GetHealth()
{
	return m_health;
}

int Actor::GetAttackDamage()
{
	return m_attackDamage;
}

void Actor::SetAttackDamage(int damage)
{
	m_attackDamage = damage;
}

void Actor::SetPosition(Position position)
{
	m_position = position;
}

AttackNotification Actor::ReceiveDamage(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
		std::cout << "An actor die : Player " << m_ownerID << std::endl;

	return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}
