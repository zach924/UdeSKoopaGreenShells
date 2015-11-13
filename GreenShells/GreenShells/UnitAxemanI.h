#pragma once
#include "Unit.h"

class UnitAxemanI : public Unit<UnitAxemanI>
{
public:
    typedef Unit<UnitAxemanI> tBase;

    static int const ATTACK_DAMAGE = 75;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 75;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 3;
    static const char* UNIT_NAME;

    UnitAxemanI(int owner);
    virtual ~UnitAxemanI();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitAxemanI* Deserialize(boost::property_tree::ptree node);
};