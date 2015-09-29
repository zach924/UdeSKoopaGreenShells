#pragma once
#include "Actor.h"

class Unit : public Actor
{
	int m_playerOwner;
public:
	Unit(int& ownerID);
	~Unit();

	int GetPlayerOwnerID();
	void SetPlayerOwnerID(int id);
	
	void NotifyNewTurn();
};

