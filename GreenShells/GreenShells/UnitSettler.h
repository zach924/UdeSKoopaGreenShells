#pragma once
#include "Unit.h"

class UnitSettler : public Unit<UnitSettler>
{
public:
    typedef Unit<UnitSettler> tBase;

    static int const ATTACK_DAMAGE = 5;
    static int const HEALTH = 100;
	static int const MOVE_RANGE = 1;

private:
    static int const UNIT_TYPE = 2;

public:
    UnitSettler(int owner);
    virtual ~UnitSettler();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSettler* Deserialize(boost::property_tree::ptree node);
};