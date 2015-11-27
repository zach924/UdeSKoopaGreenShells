#pragma once
#include "District.h"

class DistrictMonastery : public District<DistrictMonastery>
{
public:
    typedef District<DistrictMonastery> tBase;
    static const int DISTRICT_TYPE = 7;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 150;

    static const int FOOD_COST = 400;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 6;
    static const int WEAPON_YIELD = 0;
    static int const VIEW_RANGE = 3;
    static const char* NAME;

public:
    DistrictMonastery(int owner);
    ~DistrictMonastery();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictMonastery* Deserialize(boost::property_tree::ptree node);
};


