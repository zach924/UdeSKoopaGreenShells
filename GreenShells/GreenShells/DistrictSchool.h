#pragma once
#include "District.h"
#include "DistrictUniversity.h"

class DistrictSchool : public District<DistrictSchool>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 15;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 2;
    static const int UPGRADE_TYPE = DistrictUniversity::DISTRICT_TYPE;
    static constexpr char* NAME = "School";

public:
    typedef District<DistrictSchool> tBase;
    static const int DISTRICT_TYPE = 9;
    static const int FOOD_COST = 1100;

    DistrictSchool(int owner);
    ~DistrictSchool();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictSchool> Deserialize(boost::property_tree::ptree node);
};




