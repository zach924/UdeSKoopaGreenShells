#pragma once
#include "Unit.h"

class UnitMaceI : public Unit<UnitMaceI>
{
    static const int ATTACK_RANGE = 1;
    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 300;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME = "Mace MK1";

public:
    typedef Unit<UnitMaceI> tBase;
    static const int UNIT_TYPE = 8;
    static const int WEAPON_COST = 150;

    UnitMaceI(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitMaceI();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitMaceI> Deserialize(boost::property_tree::ptree node);
};