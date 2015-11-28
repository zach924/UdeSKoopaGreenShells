#pragma once
#include "District.h"
class DistrictFishery : public District<DistrictFishery>
{
public:
    typedef District<DistrictFishery> tBase;
    static const int DISTRICT_TYPE = 17;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 150;

    static const int FOOD_COST = 150;
    static const int FOOD_YIELD = 6;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 3;
    static const char* NAME;

public:
    DistrictFishery(int owner);
    ~DistrictFishery();

    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictFishery> Deserialize(boost::property_tree::ptree node);
};

