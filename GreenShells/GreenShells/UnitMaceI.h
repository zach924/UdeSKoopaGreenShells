#pragma once
#include "Unit.h"

class UnitMaceI : public Unit<UnitMaceI>
{
public:
    typedef Unit<UnitMaceI> tBase;

    static int const ATTACK_RANGE = 1;
    static int const ATTACK_DAMAGE = 75;
    static int const HEALTH = 300;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 8;
    static int const WEAPON_COST = 150;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

    UnitMaceI(int owner);
    virtual ~UnitMaceI();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitMaceI* Deserialize(boost::property_tree::ptree node);
};