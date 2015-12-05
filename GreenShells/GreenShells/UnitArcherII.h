#pragma once
#include "Unit.h"
#include "UnitArcherIII.h"

class UnitArcherII : public Unit<UnitArcherII>
{
    static const int ATTACK_DAMAGE = 75;
    static const int ATTACK_RANGE = 3;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 4;
    static const int UPGRADE_TYPE = UnitArcherIII::UNIT_TYPE;
    static constexpr char* UNIT_NAME = "Archer MK2";

public:
    typedef Unit<UnitArcherII> tBase;
    static const int UNIT_TYPE = 4;
    static const int WEAPON_COST = 200;
    
    UnitArcherII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherII();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<UnitArcherII> Deserialize(boost::property_tree::ptree node);
};