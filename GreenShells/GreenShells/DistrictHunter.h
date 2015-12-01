#pragma once
#include "District.h"
#include "DistrictFarm.h"

class DistrictHunter : public District<DistrictHunter>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 150;
    static const int FOOD_YIELD = 6;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 3;
    static const int UPGRADE_TYPE = DistrictFarm::DISTRICT_TYPE;
    static constexpr char* NAME = "Hunter";

public:
    typedef District<DistrictHunter> tBase;
    static const int DISTRICT_TYPE = 1;
    static const int FOOD_COST = 150;
    
    DistrictHunter(int owner);
    ~DistrictHunter();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictHunter> Deserialize(boost::property_tree::ptree node);
};

