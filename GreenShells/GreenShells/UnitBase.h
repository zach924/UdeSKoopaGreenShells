#pragma once

#include "AttackNotification.h" 
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class UnitBase
{
public:
	static const int MIN_ATTACK_RANGE = 1;
	static const int MAX_ATTACK_RANGE = 4; // TODO : Balancing on that
	static const int MELEE_ATTACK_RANGE = 1;

protected:
	int m_ownerID;
	int m_health;

private:
	Position m_position;

	int m_foodCost;
	int m_scienceCost;
	int m_weaponCost;

	int m_attackDamage;
	int m_attackRange;

public:
	UnitBase(int owner, int attackRange, int attackDamage);
	~UnitBase();

	virtual AttackNotification Attack(UnitBase* target) = 0;
	//virtual AttackNotification Attack(Actor* target) = 0;


	virtual void NotifyNewTurn();

	virtual boost::property_tree::ptree Serialize();
	//virtual TileBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);

};