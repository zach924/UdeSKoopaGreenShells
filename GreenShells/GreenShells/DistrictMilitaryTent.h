#pragma once
#include "District.h"

class DistrictMilitaryTent : public District<DistrictMilitaryTent>
{
public:
    typedef District<DistrictMilitaryTent> tBase;
    static const int DISTRICT_TYPE = 16;

    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 300;

    static const int FOOD_COST = 250;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;

    static const char* NAME;

public:
    DistrictMilitaryTent(int owner);
    ~DistrictMilitaryTent();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictMilitaryTent* Deserialize(boost::property_tree::ptree node);
};






