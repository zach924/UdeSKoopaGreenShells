#pragma once
#include "Unit.h"

class UnitShield : public Unit<UnitShield>
{
    static const int ATTACK_DAMAGE = 100;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 500;
    static const int ACTION_POINTS = 1;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME = "Shield";

public:
    typedef Unit<UnitShield> tBase;
    static const int UNIT_TYPE = 11;
    static const int WEAPON_COST = 450;

    UnitShield(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitShield();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitShield> Deserialize(boost::property_tree::ptree node);
};