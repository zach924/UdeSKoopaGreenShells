#pragma once
#include "District.h"

class DistrictWarehouse : public District<DistrictWarehouse>
{
public:
    typedef District<DistrictWarehouse> tBase;
    static const int DISTRICT_TYPE = 14;
    
    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 400;

    static const int FOOD_COST = 1000;
    static constexpr double FOOD_BONUS = 0.1;
    static const int VIEW_RANGE = 5;
    static const char* NAME;

public:
    DistrictWarehouse(int owner);
    ~DistrictWarehouse();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictWarehouse> Deserialize(boost::property_tree::ptree node);
};

