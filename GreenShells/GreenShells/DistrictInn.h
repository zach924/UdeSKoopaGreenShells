#pragma once
#include "District.h"

class DistrictInn : public District<DistrictInn>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;
    static const int FOOD_YIELD = 10;
    static const int SCIENCE_YIELD = 10;
    static const int WEAPON_YIELD = 0;
    static const int VIEW_RANGE = 4;
    static constexpr char* NAME = "Inn";

public:
    typedef District<DistrictInn> tBase;    
    static const int FOOD_COST = 800;
    static const int DISTRICT_TYPE = 11;

    DistrictInn(int owner);
    ~DistrictInn();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();    
    static std::shared_ptr<DistrictInn> Deserialize(boost::property_tree::ptree node);
};





