#pragma once
#include "Unit.h"

class UnitSwordsman : public Unit<UnitSwordsman>
{
public:
    typedef Unit<UnitSwordsman> tBase;

    static int const ATTACK_DAMAGE = 100;
    static int const HEALTH = 100;
    static int const MOVE_RANGE = 5;
    static int const UNIT_TYPE = 0;
	static const char* UNIT_NAME;

public:
    UnitSwordsman(int owner);
    ~UnitSwordsman();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
	virtual int GetMaxHealth();
	virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSwordsman* Deserialize(boost::property_tree::ptree node);
};