#pragma once
#include "Unit.h"

class UnitAxemanII : public Unit<UnitAxemanII>
{
    static const int ATTACK_DAMAGE = 225;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 3;
    static const int VIEW_RANGE = 4;
    static constexpr char* UNIT_NAME = "Axeman MK2";

public:
    typedef Unit<UnitAxemanII> tBase;
    static const int UNIT_TYPE = 7;
    static const int WEAPON_COST = 250;

    UnitAxemanII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitAxemanII();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitAxemanII> Deserialize(boost::property_tree::ptree node);
};