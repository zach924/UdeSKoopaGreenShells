#include "Actor.h"
#pragma once

class Unit : public Actor
{
	int m_playerOwner;
public:
	Unit();
	~Unit();

	int GetPlayerOwnerID();
	void SetPlayerOwnerID(int id);
};

