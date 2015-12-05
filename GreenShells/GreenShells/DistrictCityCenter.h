#pragma once
#include "District.h"

class DistrictCityCenter : public District<DistrictCityCenter>
{
    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 500;
    static constexpr char* NAME = "City Center";
    static const int WEAPON_YIELD = 3;
    static const int FOOD_YIELD = 5;
    static const int SCIENCE_YIELD = 3;
    static const int VIEW_RANGE = 3;

public:
    typedef District<DistrictCityCenter> tBase;
    static const int DISTRICT_TYPE = 0;
    static const int FOOD_COST = 0;
    static const int TURN_FOR_BORDER_T1 = 5; // 1 Tile
    static const int T1_BORDER_SIZE = 1;
    static const int TURN_FOR_BORDER_T2 = 50; // 2 Tile
    static const int T2_BORDER_SIZE = 2;
    static const int TURN_FOR_BORDER_T3 = 100; // 3 Tile
    static const int T3_BORDER_SIZE = 3;
    static const int TURN_FOR_BORDER_T4 = 200; // 4 Tile
    static const int T4_BORDER_SIZE = 4;
    
    DistrictCityCenter(int owner);
    ~DistrictCityCenter();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void LoadTexture();
    virtual void ChangeOwner(int newOwner);
    virtual bool CanUpgrade();
    static std::shared_ptr<DistrictCityCenter> Deserialize(boost::property_tree::ptree node);
};