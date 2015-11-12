#pragma once
#include "Unit.h"

class UnitMace : public Unit<UnitMace>
{
public:
    typedef Unit<UnitMace> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 125;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 5;
    static const char* UNIT_NAME;

    UnitMace(int owner);
    virtual ~UnitMace();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    static UnitMace* Deserialize(boost::property_tree::ptree node);
};