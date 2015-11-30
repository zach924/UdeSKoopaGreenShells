#pragma once
#include "District.h"

class DistrictSchool : public District<DistrictSchool>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 15;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 5;
    static constexpr char* NAME = "School";

public:
    typedef District<DistrictSchool> tBase;
    static const int DISTRICT_TYPE = 9;
    static const int FOOD_COST = 800;

    DistrictSchool(int owner);
    ~DistrictSchool();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual void Upgrade(Map* map);
    static std::shared_ptr<DistrictSchool> Deserialize(boost::property_tree::ptree node);
};




