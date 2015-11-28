#pragma once
#include "Unit.h"

class UnitMaceII : public Unit<UnitMaceII>
{
public:
    typedef Unit<UnitMaceII> tBase;

    static const int ATTACK_RANGE = 1;
    static const int ATTACK_DAMAGE = 150;
    static const int HEALTH = 350;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 9;
    static const int WEAPON_COST = 250;
    static const int VIEW_RANGE = 3;
    static const char* UNIT_NAME;

    UnitMaceII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitMaceII();
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

    static std::shared_ptr<UnitMaceII> Deserialize(boost::property_tree::ptree node);
};
