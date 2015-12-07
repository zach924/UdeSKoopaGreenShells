#pragma once
#include "District.h"
#include "DistrictSchool.h"

class DistrictCathedral : public District<DistrictCathedral>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 200;
    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 8;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 2;
    static const int UPGRADE_TYPE = DistrictSchool::DISTRICT_TYPE;
    static constexpr char* NAME = "Cathedral";

public:
    typedef District<DistrictCathedral> tBase;
    static const int DISTRICT_TYPE = 8;
    static const int FOOD_COST = 600;

    DistrictCathedral(int owner);
    ~DistrictCathedral();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictCathedral> Deserialize(boost::property_tree::ptree node);
};



