#pragma once
#include "Unit.h"

class UnitArcherIII : public Unit<UnitArcherIII>
{
public:
    typedef Unit<UnitArcherIII> tBase;

    static const int ATTACK_DAMAGE = 100;
    static const int ATTACK_RANGE = 4;
    static const int HEALTH = 250;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 5;
    static const int WEAPON_COST = 250;
    static const int VIEW_RANGE = 5;
    static const char* UNIT_NAME;

public:

    UnitArcherIII(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherIII();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static std::shared_ptr<UnitArcherIII> Deserialize(boost::property_tree::ptree node);
};