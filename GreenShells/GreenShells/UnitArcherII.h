#pragma once
#include "Unit.h"

class UnitArcherII : public Unit<UnitArcherII>
{
public:
    typedef Unit<UnitArcherII> tBase;

    static int const ATTACK_DAMAGE = 75;
    static int const ATTACK_RANGE = 3;
    static int const HEALTH = 200;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 4;
    static int const UNIT_TIER = 2;
    static int const VIEW_RANGE = 4;
    static const char* UNIT_NAME;

public:

    UnitArcherII(int owner);
    virtual ~UnitArcherII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual int GetUnitTier();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static UnitArcherII* Deserialize(boost::property_tree::ptree node);
};