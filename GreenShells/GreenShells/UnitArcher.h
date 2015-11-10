#pragma once
#include "Unit.h"

class UnitArcher : public Unit<UnitArcher>
{
public:
    typedef Unit<UnitArcher> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 3;
    static int const HEALTH = 100;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 1;
	static const char* UNIT_NAME;

public:

    UnitArcher(int owner);
    virtual ~UnitArcher();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
	virtual int GetMaxHealth();
	virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    static UnitArcher* Deserialize(boost::property_tree::ptree node);
};