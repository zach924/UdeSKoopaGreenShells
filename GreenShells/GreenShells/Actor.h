#pragma once
#include "Position.h"
#include "Player.h"

class Actor
{
	Player m_owner;
	Position m_position;
public:
	Actor(Player& owner);
	~Actor();

	virtual void NotifyNewTurn() = 0;
};

