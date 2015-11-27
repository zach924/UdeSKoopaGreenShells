#pragma once
#include "Unit.h"

class UnitAxemanI : public Unit<UnitAxemanI>
{
public:
    typedef Unit<UnitAxemanI> tBase;

    static int const ATTACK_DAMAGE = 200;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 150;
    static int const ACTION_POINTS = 3;
    static int const UNIT_TYPE = 6;
    static int const UNIT_TIER = 2;
    static int const VIEW_RANGE = 4;
    static const char* UNIT_NAME;

    UnitAxemanI(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitAxemanI();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitAxemanI> Deserialize(boost::property_tree::ptree node);
};