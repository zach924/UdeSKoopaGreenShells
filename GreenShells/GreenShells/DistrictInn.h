#pragma once
#include "District.h"

class DistrictInn : public District<DistrictInn>
{
public:
    typedef District<DistrictInn> tBase;
    static const int DISTRICT_TYPE = 11;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 300;

    static const int FOOD_COST = 800;
    static const int FOOD_YIELD = 10;
    static const int SCIENCE_YIELD = 10;
    static const int WEAPON_YIELD = 0;
    static int const VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictInn(int owner);
    ~DistrictInn();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictInn* Deserialize(boost::property_tree::ptree node);
};





