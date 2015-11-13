#pragma once
#include "Unit.h"

class UnitArcherI : public Unit<UnitArcherI>
{
public:
    typedef Unit<UnitArcherI> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 3;
    static int const HEALTH = 100;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 1;
    static const char* UNIT_NAME;

public:

    UnitArcherI(int owner);
    virtual ~UnitArcherI();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    static UnitArcherI* Deserialize(boost::property_tree::ptree node);
};