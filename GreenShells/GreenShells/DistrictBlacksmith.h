#pragma once
#include "District.h"
#include "DistrictStable.h"

class DistrictBlacksmith : public District<DistrictBlacksmith>
{
    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 100;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 6;
    static const int VIEW_RANGE = 2;
    static const int UPGRADE_TYPE = DistrictStable::DISTRICT_TYPE;
    static constexpr char* NAME = "Blacksmith";

public:
    typedef District<DistrictBlacksmith> tBase;
    static const int DISTRICT_TYPE = 4;
    static const int FOOD_COST = 150;
    
    DistrictBlacksmith(int owner);
    ~DistrictBlacksmith();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictBlacksmith> Deserialize(boost::property_tree::ptree node);
};

