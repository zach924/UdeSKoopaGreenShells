#pragma once
#include "Unit.h"

class UnitSwordsmanI : public Unit<UnitSwordsmanI>
{
    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME ="Swordsman MK1";

public:
    typedef Unit<UnitSwordsmanI> tBase;
    static const int UNIT_TYPE = 0;
    static const int WEAPON_COST = 50;

    UnitSwordsmanI(int owner, bool hasBonusActionPoint = false);
    ~UnitSwordsmanI();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual void Upgrade(Map* map);
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitSwordsmanI> Deserialize(boost::property_tree::ptree node);
};