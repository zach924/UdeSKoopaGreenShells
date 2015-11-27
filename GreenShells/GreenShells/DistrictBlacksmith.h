#pragma once
#include "District.h"

class DistrictBlacksmith : public District<DistrictBlacksmith>
{
public:
    typedef District<DistrictBlacksmith> tBase;
    static const int DISTRICT_TYPE = 4;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 250;

    static const int FOOD_COST = 150;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 75;
    static int const VIEW_RANGE = 3;
    static const char* NAME;

public:
    DistrictBlacksmith(int owner);
    ~DistrictBlacksmith();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Upgrade(Map* map);

    static std::shared_ptr<DistrictBlacksmith> Deserialize(boost::property_tree::ptree node);
};

