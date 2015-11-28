#pragma once
#include "Unit.h"

class UnitShield : public Unit<UnitShield>
{
public:
    typedef Unit<UnitShield> tBase;

    static const int ATTACK_DAMAGE = 100;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 500;
    static const int ACTION_POINTS = 1;
    static const int UNIT_TYPE = 11;
    static const int WEAPON_COST = 450;
    static const int VIEW_RANGE = 3;
    static const char* UNIT_NAME;

    UnitShield(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitShield();
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

    static std::shared_ptr<UnitShield> Deserialize(boost::property_tree::ptree node);
};