#pragma once
#include "District.h"

class DistrictTavern : public District<DistrictTavern>
{
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;
    static const int FOOD_YIELD = 10;
    static const int SCIENCE_YIELD = 0;
    static const int WEAPON_YIELD = 10;
    static const int VIEW_RANGE = 4;
    static constexpr char* NAME = "Tavern";

public:
    typedef District<DistrictTavern> tBase;
    static const int DISTRICT_TYPE = 12;
    static const int FOOD_COST = 800;
    
    DistrictTavern(int owner);
    ~DistrictTavern();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictTavern> Deserialize(boost::property_tree::ptree node);
};





