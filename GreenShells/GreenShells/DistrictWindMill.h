#pragma once
#include "District.h"
#include "DistrictWarehouse.h"

class DistrictWindMill : public District<DistrictWindMill>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 350;

    static const int FOOD_YIELD = 15;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 5;
    static const int UPGRADE_TYPE = DistrictWarehouse::DISTRICT_TYPE;
    static constexpr char* NAME = "Windmill";

public:
    typedef District<DistrictWindMill> tBase;
    static const int DISTRICT_TYPE = 3;
    static const int FOOD_COST = 400;

public:
    DistrictWindMill(int owner);
    ~DistrictWindMill();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictWindMill> Deserialize(boost::property_tree::ptree node);
};

