#pragma once
#include "Unit.h"

class UnitArcherIII : public Unit<UnitArcherIII>
{
public:
    typedef Unit<UnitArcherIII> tBase;

    static int const ATTACK_DAMAGE = 100;
    static int const ATTACK_RANGE = 4;
    static int const HEALTH = 250;
    static int const MOVE_RANGE = 2;
    static int const UNIT_TYPE = 5;
    static int const UNIT_TIER = 3;
    static const char* UNIT_NAME;

public:

    UnitArcherIII(int owner);
    virtual ~UnitArcherIII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetUnitTier();
    virtual void Heal(int health);

    static UnitArcherIII* Deserialize(boost::property_tree::ptree node);
};