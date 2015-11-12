#pragma once
#include "Unit.h"

class UnitSwordsman : public Unit<UnitSwordsman>
{
public:
    typedef Unit<UnitSwordsman> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const HEALTH = 100;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 0;
    static int const VIEW_RANGE = 2;
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
    virtual int GetViewRange();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSwordsman* Deserialize(boost::property_tree::ptree node);
};