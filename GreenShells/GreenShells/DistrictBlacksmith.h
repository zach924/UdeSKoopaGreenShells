#pragma once
#include "District.h"

class DistrictBlacksmith : public District<DistrictBlacksmith>
{
public:
    typedef District<DistrictBlacksmith> tBase;
    static const int DISTRICT_TYPE = 4;

    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 100;

    static const int FOOD_COST = 150;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 6;
    static int const VIEW_RANGE = 3;
    static const char* NAME;

public:
    DistrictBlacksmith(int owner);
    ~DistrictBlacksmith();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictBlacksmith* Deserialize(boost::property_tree::ptree node);
};

