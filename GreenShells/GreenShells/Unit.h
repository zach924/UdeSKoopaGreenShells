#pragma once
#include "Actor.h"

#include "Actor.h"


class Unit : public Actor
{
public:
	Unit(int& ownerID);
    ~Unit();
	
	void NotifyNewTurn();

    virtual boost::property_tree::ptree Serialize();
};

