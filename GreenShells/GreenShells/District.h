#pragma once
#include "Actor.h"

class District : public Actor
{
public:
	District(Player& owner);
	~District();

	void NotifyNewTurn();
};

