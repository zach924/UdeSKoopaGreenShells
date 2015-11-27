#pragma once
#include "District.h"

class DistrictWatchTower : public District<DistrictWatchTower>
{
public:
    typedef District<DistrictWatchTower> tBase;
    static const int DISTRICT_TYPE = 10;

    static const int ATTACK_DAMAGE =50;
    static const int HEALTH = 150;

    static const int FOOD_COST = 75;
    static int const VIEW_RANGE = 5;
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
    virtual int GetViewRange();

    static DistrictWatchTower* Deserialize(boost::property_tree::ptree node);
};




