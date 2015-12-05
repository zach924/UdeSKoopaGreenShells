#pragma once
#include "District.h"

class DistrictMilitaryTent : public District<DistrictMilitaryTent>
{
    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 400;
    static const int VIEW_RANGE = 3;
    static constexpr char* NAME = "Military Tent";

public:
    typedef District<DistrictMilitaryTent> tBase;
    static constexpr double WEAPON_BONUS = 0.1;
    static const int DISTRICT_TYPE = 16;
    static const int FOOD_COST = 1000;
    static constexpr double ATTACK_MULTIPLIER = 0.1;

    DistrictMilitaryTent(int owner);
    ~DistrictMilitaryTent();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictMilitaryTent> Deserialize(boost::property_tree::ptree node);
};






