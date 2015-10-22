#pragma once
#include "District.h"

class DistrictCityCenter : public District<DistrictCityCenter>
{
public :
	typedef District<DistrictCityCenter> tBase;
	static const int DISTRICT_TYPE = 0;

	static const int ATTACK_DAMAGE = 50;
	static const int HEALTH = 200;

public:
	DistrictCityCenter(int owner);
	~DistrictCityCenter();

    void LoadTexture();

	void ChangeOwner(int owner);

	virtual int GetTypeAsInt();

	virtual void Repair(int repairValue);


	static DistrictCityCenter* Deserialize(boost::property_tree::ptree node);
};