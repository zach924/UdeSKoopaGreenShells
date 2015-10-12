#pragma once
#include "Actor.h"

class Unit : public Actor
{
public:
	static const int MIN_ATTACK_RANGE = 1;
	static const int MAX_ATTACK_RANGE = 4; // TODO : Balancing on that
	static const int MELEE_ATTACK_RANGE = 1;
	
private:
	int m_attackRange;

public:
	Unit(int ownerID, int attckRange, int attackDamage = 50);
    ~Unit();

	virtual AttackNotification Attack(Actor* target)=0;
	
	void NotifyNewTurn();
    virtual boost::property_tree::ptree Serialize();
};

