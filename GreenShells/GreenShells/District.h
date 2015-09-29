#include "Actor.h"
#pragma once
class District : public Actor
{
	int m_playerOwner;
public:
	District();
	~District();

	int GetPlayerOwnerID();
	void SetPlayerOwnerID(int ID);

};

