#pragma once
#include "District.h"

class DistrictCityCenter : public District<DistrictCityCenter>
{
public:
    typedef District<DistrictCityCenter> tBase;
    static const int DISTRICT_TYPE = 0;

    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 1000;
    static const char* NAME;
    static const int WEAPON_YIELD = 75;
    static const int FOOD_YIELD = 75;
    static const int SCIENCE_YIELD = 1;
    static const int FOOD_COST = 300;
    static const int WEAPON_BONUS = 0;
    static int const VIEW_RANGE = 5;

    static const int TURN_FOR_BORDER_T1 = 5; // 1 Tile
    static const int T1_BORDER_SIZE = 1;
    static const int TURN_FOR_BORDER_T2 = 50; // 2 Tile
    static const int T2_BORDER_SIZE = 2;
    static const int TURN_FOR_BORDER_T3 = 100; // 3 Tile
    static const int T3_BORDER_SIZE = 3;
    static const int TURN_FOR_BORDER_T4 = 200; // 4 Tile
    static const int T4_BORDER_SIZE = 4;

public:
    DistrictCityCenter(int owner);
    ~DistrictCityCenter();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();

    virtual void ChangeOwner(int newOwner);

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt(); 
    virtual int GetViewRange();

    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    static std::shared_ptr<DistrictCityCenter> Deserialize(boost::property_tree::ptree node);
};