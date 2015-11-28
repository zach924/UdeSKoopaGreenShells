#pragma once
#include "District.h"

class DistrictMilitaryTent : public District<DistrictMilitaryTent>
{
public:
    typedef District<DistrictMilitaryTent> tBase;
    static const int DISTRICT_TYPE = 16;

    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 400;
    static const int FOOD_COST = 1000;

    static constexpr double WEAPON_BONUS = 0.1;

    static const int VIEW_RANGE = 3;
    static const char* NAME;

public:
    DistrictMilitaryTent(int owner);
    ~DistrictMilitaryTent();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictMilitaryTent> Deserialize(boost::property_tree::ptree node);
};






