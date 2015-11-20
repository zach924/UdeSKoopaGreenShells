#pragma once
#include "District.h"

class DistrictCityCenter : public District<DistrictCityCenter>
{
public:
    typedef District<DistrictCityCenter> tBase;
    static const int DISTRICT_TYPE = 0;

    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 200;
    static const char* NAME;
    static const int TURN_FOR_BORDER_T1 = 5; // 1 Tile
    static const int T1_BORDER_SIZE = 1;
    static const int TURN_FOR_BORDER_T2 = 50; // 2 Tile
    static const int T2_BORDER_SIZE = 2;
    static const int TURN_FOR_BORDER_T3 = 100; // 3 Tile
    static const int T3_BORDER_SIZE = 3;
    static const int TURN_FOR_BORDER_T4 = 200; // 4 Tile
    static const int T4_BORDER_SIZE = 4;
    static int const VIEW_RANGE = 3;

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

    static DistrictCityCenter* Deserialize(boost::property_tree::ptree node);
};