#pragma once
#include "District.h"
#include "DistrictFort.h"

class DistrictStable : public District<DistrictStable>
{
    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 150;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 10;
    static const int VIEW_RANGE = 4;
    static const int UPGRADE_TYPE = DistrictFort::DISTRICT_TYPE;
    static constexpr char* NAME = "Stable";

public:
    typedef District<DistrictStable> tBase;
    static const int DISTRICT_TYPE = 5;
    static const int FOOD_COST = 400;
    
    DistrictStable(int owner);
    ~DistrictStable();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictStable> Deserialize(boost::property_tree::ptree node);
};



