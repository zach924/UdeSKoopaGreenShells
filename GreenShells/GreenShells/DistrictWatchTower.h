#pragma once
#include "District.h"

class DistrictWatchTower : public District<DistrictWatchTower>
{
    static const int ATTACK_DAMAGE =50;
    static const int HEALTH = 150;
    static const int VIEW_RANGE = 5;
    static constexpr char* NAME = "Watch Tower";

public:
    typedef District<DistrictWatchTower> tBase;
    static const int DISTRICT_TYPE = 10;
    static const int FOOD_COST = 75;

    DistrictWatchTower(int owner);
    ~DistrictWatchTower();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictWatchTower> Deserialize(boost::property_tree::ptree node);
};




