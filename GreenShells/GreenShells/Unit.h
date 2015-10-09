#pragma once
#include "Actor.h"

#include "Actor.h"


class Unit : public Actor
{
public:
	Unit(const int& ownerID,const Position& pos);
    ~Unit();
	
	void NotifyNewTurn();

   virtual boost::property_tree::ptree Serialize();
};

