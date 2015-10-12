#pragma once
#include "Actor.h"

class District : public Actor
{
public:
	District(int ownerID);
	~District();

	void NotifyNewTurn();
	virtual boost::property_tree::ptree Serialize();
};

