#pragma once
#include "District.h"

class DistrictMonastery : public District<DistrictMonastery>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 150;

    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 6;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 3;
    static constexpr char* NAME = "Monastery";

public:
    typedef District<DistrictMonastery> tBase;
    static const int DISTRICT_TYPE = 7;
    static const int FOOD_COST = 400;

    DistrictMonastery(int owner);
    ~DistrictMonastery();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictMonastery> Deserialize(boost::property_tree::ptree node);
};


