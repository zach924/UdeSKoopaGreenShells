#pragma once
#include "District.h"

class DistrictFarm : public District<DistrictFarm>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 150;
    static const int FOOD_YIELD = 10;
    static const int WEAPON_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int VIEW_RANGE = 4;
    static constexpr char* NAME = "Farm";

public:
    typedef District<DistrictFarm> tBase;
    static const int DISTRICT_TYPE = 2;
    static const int FOOD_COST = 200;
    
    DistrictFarm(int owner);
    ~DistrictFarm();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictFarm> Deserialize(boost::property_tree::ptree node);
};