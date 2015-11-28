#pragma once
#include "District.h"

class DistrictSchool : public District<DistrictSchool>
{
public:
    typedef District<DistrictSchool> tBase;
    static const int DISTRICT_TYPE = 9;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;

    static const int FOOD_COST = 800;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 15;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 5;
    static const char* NAME;

public:
    DistrictSchool(int owner);
    ~DistrictSchool();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictSchool> Deserialize(boost::property_tree::ptree node);
};




