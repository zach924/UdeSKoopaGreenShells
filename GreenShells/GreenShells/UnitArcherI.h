#pragma once
#include "Unit.h"

class UnitArcherI : public Unit<UnitArcherI>
{
public:
    typedef Unit<UnitArcherI> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 3;
    static int const HEALTH = 150;
    static int const MOVE_RANGE = 2;
    static int const UNIT_TYPE = 3;
    static int const UNIT_TIER = 1;
    static int const VIEW_RANGE = 4;
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
    virtual int GetViewRange();
    virtual int GetUnitTier();
    virtual void Heal(int health);

    static UnitArcherI* Deserialize(boost::property_tree::ptree node);
};