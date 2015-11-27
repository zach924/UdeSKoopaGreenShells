#pragma once
#include "Unit.h"

class UnitSettler : public Unit<UnitSettler>
{
public:
    typedef Unit<UnitSettler> tBase;

    static int const ATTACK_DAMAGE = 5;
    static int const HEALTH = 50;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 12;
    static int const UNIT_TIER = 2;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSettler(int owner);
    virtual ~UnitSettler();
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
    virtual void Upgrade(Map* map);

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitSettler> Deserialize(boost::property_tree::ptree node);
};