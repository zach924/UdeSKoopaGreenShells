#pragma once
#include "Unit.h"

class UnitArcherII : public Unit<UnitArcherII>
{
public:
    typedef Unit<UnitArcherII> tBase;

    static const int ATTACK_DAMAGE = 75;
    static const int ATTACK_RANGE = 3;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 4;
    static const int WEAPON_COST = 100;
    static const int VIEW_RANGE = 4;
    static const char* UNIT_NAME;

public:

    UnitArcherII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherII();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static std::shared_ptr<UnitArcherII> Deserialize(boost::property_tree::ptree node);
};