#pragma once
#include "District.h"

class DistrictTavern : public District<DistrictTavern>
{
public:
    typedef District<DistrictTavern> tBase;
    static const int DISTRICT_TYPE = 12;

    static const int ATTACK_DAMAGE = 25;
    static const int HEALTH = 300;

    static const int FOOD_COST = 250;
    static const int FOOD_BONUS = 75;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 100;
    static int const VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictTavern(int owner);
    ~DistrictTavern();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictTavern* Deserialize(boost::property_tree::ptree node);
};





