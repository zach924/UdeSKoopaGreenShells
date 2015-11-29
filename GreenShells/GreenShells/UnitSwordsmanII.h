#pragma once
#include "Unit.h"

class UnitSwordsmanII : public Unit<UnitSwordsmanII>
{
    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 250;
    static const int ACTION_POINTS = 2;
    static const int VIEW_RANGE = 3;
    static constexpr char* UNIT_NAME = "Swordsman MK2";

public:
    typedef Unit<UnitSwordsmanII> tBase;
    static const int UNIT_TYPE = 1;
    static const int WEAPON_COST = 100;
    
    UnitSwordsmanII(int owner, bool hasBonusActionPoint = false);
    ~UnitSwordsmanII();
    virtual std::shared_ptr<UnitBase> Clone();
    virtual void LoadTexture();
    virtual bool CanUpgrade();
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);
    static std::shared_ptr<UnitSwordsmanII> Deserialize(boost::property_tree::ptree node);
};

