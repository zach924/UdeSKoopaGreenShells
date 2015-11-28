#pragma once
#include "District.h"

class DistrictFort : public District<DistrictFort>
{
public:
    typedef District<DistrictFort> tBase;
    static const int DISTRICT_TYPE = 6;

    static const int ATTACK_DAMAGE = 200;
    static const int HEALTH = 400;

    static const int FOOD_COST = 600;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 15;
    static const int VIEW_RANGE = 5;
    static const char* NAME;

public:
    DistrictFort(int owner);
    ~DistrictFort();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictFort> Deserialize(boost::property_tree::ptree node);
};



