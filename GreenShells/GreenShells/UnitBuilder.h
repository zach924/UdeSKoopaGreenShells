#pragma once
#include "Unit.h"

class UnitBuilder : public Unit<UnitBuilder>
{
    static const int ATTACK_DAMAGE = 25;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 5;
    static constexpr char* UNIT_NAME = "Builder";

public:
    typedef Unit<UnitBuilder> tBase;
    static const int UNIT_TYPE = 13;
    static const int WEAPON_COST = 0;
    static const int FOOD_COST = 75;
    
    UnitBuilder(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitBuilder();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<UnitBuilder> Deserialize(boost::property_tree::ptree node);
};



