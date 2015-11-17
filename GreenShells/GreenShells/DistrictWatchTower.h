#pragma once
#include "District.h"

class DistrictWatchTower : public District<DistrictWatchTower>
{
public:
    typedef District<DistrictWatchTower> tBase;
    static const int DISTRICT_TYPE = 10;

    static const int ATTACK_DAMAGE =750;
    static const int HEALTH = 200;

    static const int FOOD_COST = 75;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;

    static const char* NAME;

public:
    DistrictWatchTower(int owner);
    ~DistrictWatchTower();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictWatchTower* Deserialize(boost::property_tree::ptree node);
};




