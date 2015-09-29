#pragma once
#include "Actor.h"

class District : public Actor
{
public:
	District(int& ownerID);
	~District();

	void NotifyNewTurn();
};

