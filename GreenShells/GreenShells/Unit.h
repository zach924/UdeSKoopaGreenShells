#pragma once
#include "Actor.h"

class Unit : public Actor
{
public:
	static const int MIN_ATTACK_RANGE = 1;
	static const int MAX_ATTACK_RANGE = 4;
	static const int MELEE_ATTACK_RANGE = 1;
	
private:
	int m_attackRange;

public:
	Unit(int& ownerID, int attckRange);
	~Unit();
	
	void NotifyNewTurn();
};

