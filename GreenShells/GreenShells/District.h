#pragma once
#include "Actor.h"

class District : public Actor
{
	int m_playerOwner;
public:
	District(int& ownerID);
	~District();

	int GetPlayerOwnerID();
	void NotifyNewTurn();
	void SetPlayerOwnerID(int ID);

};

