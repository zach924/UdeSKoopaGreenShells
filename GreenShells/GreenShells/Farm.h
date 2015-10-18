#pragma once
#include "District.h"

class Farm : public District<Farm>
{
public:
	typedef District<Farm> tBase;

	static const int HEALTH = 75;

public:
	Farm(int owner);
	~Farm();

	virtual void Repair(int repairValue);

	virtual  boost::property_tree::ptree Serialize();
};