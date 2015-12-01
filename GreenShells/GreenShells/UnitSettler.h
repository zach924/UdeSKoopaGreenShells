#pragma once
#include "Unit.h"

class UnitSettler : public Unit<UnitSettler>
{
    static const int ATTACK_DAMAGE = 5;
    static const int HEALTH = 50;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME = "Settler";

public:
    typedef Unit<UnitSettler> tBase;
    static const int WEAPON_COST = 0;
    static const int FOOD_COST = 700;
    static const int UNIT_TYPE = 12;

    UnitSettler(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitSettler();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitSettler> Deserialize(boost::property_tree::ptree node);
};