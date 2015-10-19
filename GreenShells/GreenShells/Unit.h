#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
	Unit(int& ownerID);
    ~Unit();
	
	void NotifyNewTurn();

    virtual boost::property_tree::ptree Serialize();
};

