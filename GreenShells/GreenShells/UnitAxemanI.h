#pragma once
#include "Unit.h"
#include "UnitAxemanII.h"

class UnitAxemanI : public Unit<UnitAxemanI>
{
    static const int ATTACK_DAMAGE = 125;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 150;
    static const int ACTION_POINTS = 3;
    static const int VIEW_RANGE = 3;
    static const int UPGRADE_TYPE = UnitAxemanII::UNIT_TYPE;
    static constexpr char* UNIT_NAME = "Axeman MK1";

public:
    typedef Unit<UnitAxemanI> tBase;
    static const int UNIT_TYPE = 6;
    static const int WEAPON_COST = 150;

    UnitAxemanI(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitAxemanI();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitAxemanI> Deserialize(boost::property_tree::ptree node);
};