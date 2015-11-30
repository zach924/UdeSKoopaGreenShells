#pragma once
#include "Unit.h"

class UnitArcherIII : public Unit<UnitArcherIII>
{
    static const int ATTACK_DAMAGE = 100;
    static const int ATTACK_RANGE = 4;
    static const int HEALTH = 250;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 5;
    static constexpr char* UNIT_NAME = "Archer MK3";

public:
    typedef Unit<UnitArcherIII> tBase;
    static const int UNIT_TYPE = 5;
    static const int WEAPON_COST = 250;
    
    UnitArcherIII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherIII();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<UnitArcherIII> Deserialize(boost::property_tree::ptree node);
};