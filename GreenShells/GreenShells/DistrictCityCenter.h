#pragma once
#include "District.h"

class DistrictCityCenter : public District<DistrictCityCenter>
{
public:
    typedef District<DistrictCityCenter> tBase;
    static const int DISTRICT_TYPE = 0;

    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 200;
	static const char* NAME;

public:
    DistrictCityCenter(int owner);
    ~DistrictCityCenter();
    virtual DistrictBase* Clone();
    void LoadTexture();

    void ChangeOwner(int owner);

	virtual int GetMaxHealth();
	virtual const char* GetName();
    virtual int GetTypeAsInt();

    virtual void Repair(int repairValue);
	virtual bool CanUpgrade();

    static DistrictCityCenter* Deserialize(boost::property_tree::ptree node);
};