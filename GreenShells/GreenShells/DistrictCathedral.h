#pragma once
#include "District.h"

class DistrictCathedral : public District<DistrictCathedral>
{
public:
    typedef District<DistrictCathedral> tBase;
    static const int DISTRICT_TYPE = 8;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 200;

    static const int FOOD_COST = 600;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 10;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictCathedral(int owner);
    ~DistrictCathedral();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictCathedral> Deserialize(boost::property_tree::ptree node);
};



