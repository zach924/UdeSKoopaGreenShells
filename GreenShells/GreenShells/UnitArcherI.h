#pragma once
#include "Unit.h"
#include "UnitArcherII.h"

class UnitArcherI : public Unit<UnitArcherI>
{
    static const int ATTACK_DAMAGE = 50;
    static const int ATTACK_RANGE = 3;
    static const int HEALTH = 150;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static const int UPGRADE_TYPE = UnitArcherII::UNIT_TYPE;
    static constexpr char* UNIT_NAME = "Archer MK1";

public:
    typedef Unit<UnitArcherI> tBase;
    static const int UNIT_TYPE = 3;
    static const int WEAPON_COST = 100;

    UnitArcherI(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherI();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    static std::shared_ptr<UnitArcherI> Deserialize(boost::property_tree::ptree node);
};