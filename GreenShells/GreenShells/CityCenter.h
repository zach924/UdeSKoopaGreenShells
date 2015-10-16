#pragma once
#include "District.h"

class CityCenter : public District<CityCenter>
{
public :
	typedef District<CityCenter> tBase;

	static const int ATTACK_DAMAGE = 50;
	static const int HEALTH = 200;

public:
	CityCenter(int owner);
	~CityCenter();

	void ChangeOwner(int owner);

	virtual void Repair(int repairValue);

	virtual  boost::property_tree::ptree Serialize();

};