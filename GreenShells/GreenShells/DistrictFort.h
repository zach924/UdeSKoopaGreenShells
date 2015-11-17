#pragma once
#include "District.h"

class DistrictFort : public District<DistrictFort>
{
public:
    typedef District<DistrictFort> tBase;
    static const int DISTRICT_TYPE = 6;

    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 400;

    static const int FOOD_COST = 150;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 175;

    static const char* NAME;

public:
    DistrictFort(int owner);
    ~DistrictFort();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictFort* Deserialize(boost::property_tree::ptree node);
};



