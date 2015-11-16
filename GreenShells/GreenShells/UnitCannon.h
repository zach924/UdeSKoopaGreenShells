#pragma once
#include "Unit.h"

class UnitCannon : public Unit<UnitCannon>
{
public:
    typedef Unit<UnitCannon> tBase;

    static int const ATTACK_DAMAGE = 200;
    static int const ATTACK_RANGE = 4;
    static int const HEALTH = 100;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 10;
    static const char* UNIT_NAME;

    UnitCannon(int owner);
    virtual ~UnitCannon();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    static UnitCannon* Deserialize(boost::property_tree::ptree node);
};

