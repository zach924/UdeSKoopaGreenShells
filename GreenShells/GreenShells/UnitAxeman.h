#pragma once
#include "Unit.h"

class UnitAxeman : public Unit<UnitAxeman>
{
public:
    typedef Unit<UnitAxeman> tBase;

    static int const ATTACK_DAMAGE = 75;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 75;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 3;
    static const char* UNIT_NAME;

    UnitAxeman(int owner);
    virtual ~UnitAxeman();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    static UnitAxeman* Deserialize(boost::property_tree::ptree node);
};

