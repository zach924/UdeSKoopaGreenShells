#pragma once
#include "Position.h"
#include "Player.h"

class Actor
{
protected:
	int m_ownerID;

private:
	Position m_position;
public:
	Actor(int ownerID, Position position = Position(-1,-1));
	~Actor();

	void SetOwnerID(int ID);
	int GetOwnerID();

	virtual void NotifyNewTurn() = 0;
};

