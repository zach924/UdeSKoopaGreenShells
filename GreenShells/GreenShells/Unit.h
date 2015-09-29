#pragma once
#include "Actor.h"

class Unit : public Actor
{
public:
	Unit(int& ownerID);
	~Unit();
	
	void NotifyNewTurn();
};

