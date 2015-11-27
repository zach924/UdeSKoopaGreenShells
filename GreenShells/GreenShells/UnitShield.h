#pragma once
#include "Unit.h"

class UnitShield : public Unit<UnitShield>
{
public:
    typedef Unit<UnitShield> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 400;
    static int const ACTION_POINTS = 1;
    static int const UNIT_TYPE = 11;
    static int const UNIT_TIER = 3;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

    UnitShield(int owner);
    virtual ~UnitShield();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual int GetUnitTier();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitShield> Deserialize(boost::property_tree::ptree node);
};