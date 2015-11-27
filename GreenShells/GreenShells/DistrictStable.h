#pragma once
#include "District.h"

class DistrictStable : public District<DistrictStable>
{
public:
    typedef District<DistrictStable> tBase;
    static const int DISTRICT_TYPE = 5;

    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 150;

    static const int FOOD_COST = 400;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 10;
    static int const VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictStable(int owner);
    ~DistrictStable();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictStable* Deserialize(boost::property_tree::ptree node);
};



