#pragma once
#include "District.h"

class DistrictFortress : public District<DistrictFortress>
{
    static const int ATTACK_DAMAGE = 300;
    static const int HEALTH = 600;

    static const int FOOD_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 15;
    static const int VIEW_RANGE = 3;
    static constexpr char* NAME = "Fortress";

public:
    typedef District<DistrictFortress> tBase;
    static const int DISTRICT_TYPE = 15;
    static const int FOOD_COST = 0;

    DistrictFortress(int owner);
    ~DistrictFortress();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictFortress> Deserialize(boost::property_tree::ptree node);
};



