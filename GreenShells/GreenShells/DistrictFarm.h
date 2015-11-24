#pragma once
#include "District.h"

class DistrictFarm : public District<DistrictFarm>
{
public:
    typedef District<DistrictFarm> tBase;
    static const int DISTRICT_TYPE = 2;
    static const int FOOD_YIELD = 3;
    static const int WEAPON_YIELD = 0;
    static const int SCIENCE_YIELD = 0;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;

    static const int FOOD_COST = 200;
    static const int FOOD_BONUS = 100;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;
    static int const VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictFarm(int owner);
    ~DistrictFarm();
    virtual std::shared_ptr<DistrictBase> Clone();
    virtual void ChangeOwner(int newOwner);
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictFarm> Deserialize(boost::property_tree::ptree node);
};