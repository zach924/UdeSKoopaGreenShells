#pragma once
#include "Actor.h"

class Unit : public Actor
{
public:
	Unit(Player& owner);
	~Unit();

	void NotifyNewTurn();
};

