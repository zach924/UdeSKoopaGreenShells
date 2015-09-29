#pragma once
#include "Position.h"
#include "Player.h"

class Actor
{
	int m_ownerID;
	Position m_position;
public:
	Actor(int ownerID, Position position = Position(-1,-1));
	~Actor();

	virtual void NotifyNewTurn();
};

