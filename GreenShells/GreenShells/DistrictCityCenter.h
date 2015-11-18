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
    static const int TURN_FOR_BORDER_T2 = 50; // 2 Tile
    static const int TURN_FOR_BORDER_T3 = 100; // 3 Tile
    static const int TURN_FOR_BORDER_T4 = 200; // 4 Tile

public:
    DistrictCityCenter(int owner);
    ~DistrictCityCenter();
    virtual DistrictBase* Clone();
    void LoadTexture();

    virtual void ChangeOwner(int newOwner);

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    static DistrictCityCenter* Deserialize(boost::property_tree::ptree node);
};