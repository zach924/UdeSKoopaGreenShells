#pragma once
#include "District.h"
#include "DistrictFortress.h"

class DistrictFort : public District<DistrictFort>
{
    static const int ATTACK_DAMAGE = 200;
    static const int HEALTH = 400;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 15;
    static const int VIEW_RANGE = 2;
    static const int UPGRADE_TYPE = DistrictFortress::DISTRICT_TYPE;
    static constexpr char* NAME = "Fort";

public:
    typedef District<DistrictFort> tBase;
    static const int DISTRICT_TYPE = 6;
    static const int FOOD_COST = 600;

    DistrictFort(int owner);
    ~DistrictFort();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictFort> Deserialize(boost::property_tree::ptree node);
};



