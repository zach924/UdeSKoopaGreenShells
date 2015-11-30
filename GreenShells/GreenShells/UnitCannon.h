#pragma once
#include "Unit.h"

class UnitCannon : public Unit<UnitCannon>
{
    static const int ATTACK_DAMAGE = 200;
    static const int ATTACK_RANGE = 4;
    static const int HEALTH = 150;
    static const int ACTION_POINTS = 1;
    static const int VIEW_RANGE = 5;
    static constexpr char* UNIT_NAME = "Cannon";

public:
    typedef Unit<UnitCannon> tBase;
    static const int UNIT_TYPE = 10;
    static const int WEAPON_COST = 450;
    
    UnitCannon(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitCannon();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<UnitCannon> Deserialize(boost::property_tree::ptree node);
};

