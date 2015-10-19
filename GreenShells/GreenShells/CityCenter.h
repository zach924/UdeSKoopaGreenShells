#pragma once
#include "District.h"

class CityCenter : public District<CityCenter>
{
public :
	typedef District<CityCenter> tBase;
	static const int DISTRICT_TYPE = 0;

	static const int ATTACK_DAMAGE = 50;
	static const int HEALTH = 200;

public:
	CityCenter(int owner);
	~CityCenter();

	void ChangeOwner(int owner);

	virtual int GetTypeAsInt();

	virtual void Repair(int repairValue);
	
};