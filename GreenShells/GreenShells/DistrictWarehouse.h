#pragma once
#include "District.h"

class DistrictWarehouse : public District<DistrictWarehouse>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 400;
    static const int VIEW_RANGE = 2;
    static const int FOOD_YIELD = 10;
    static const int WEAPON_YIELD = 10;
    static const int SCIENCE_YIELD =10;
    static constexpr char* NAME = "Warehouse";

public:
    typedef District<DistrictWarehouse> tBase;
    static const int DISTRICT_TYPE = 14;
    static const int FOOD_COST = 1000;
    static constexpr double FOOD_BONUS = 0.1;

    DistrictWarehouse(int owner);
    ~DistrictWarehouse();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictWarehouse> Deserialize(boost::property_tree::ptree node);
};

