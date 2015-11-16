#pragma once
#include "Unit.h"

class UnitSettler : public Unit<UnitSettler>
{
public:
    typedef Unit<UnitSettler> tBase;

    static int const ATTACK_DAMAGE = 5;
    static int const HEALTH = 50;
    static int const MOVE_RANGE = 2;
    static int const UNIT_TYPE = 12;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSettler(int owner);
    virtual ~UnitSettler();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSettler* Deserialize(boost::property_tree::ptree node);
};