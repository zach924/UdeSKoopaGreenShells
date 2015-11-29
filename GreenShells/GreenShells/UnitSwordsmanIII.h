#pragma once
#include "Unit.h"

class UnitSwordsmanIII : public Unit<UnitSwordsmanIII>
{
    static const int ATTACK_DAMAGE = 100;
    static const int HEALTH = 300;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME = "Swordsman MK3";

public:
    typedef Unit<UnitSwordsmanIII> tBase;
    static const int UNIT_TYPE = 2;
    static const int WEAPON_COST = 200;

    UnitSwordsmanIII(int owner, bool hasBonusActionPoint = false);
    ~UnitSwordsmanIII();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitSwordsmanIII> Deserialize(boost::property_tree::ptree node);
};