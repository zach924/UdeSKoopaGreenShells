#pragma once
#include "District.h"

class DistrictSchool : public District<DistrictSchool>
{
public:
    typedef District<DistrictSchool> tBase;
    static const int DISTRICT_TYPE = 9;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 350;

    static const int FOOD_COST = 400;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 175;
    static const int WEAPON_BONUS = 0;

    static const char* NAME;

public:
    DistrictSchool(int owner);
    ~DistrictSchool();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictSchool* Deserialize(boost::property_tree::ptree node);
};




