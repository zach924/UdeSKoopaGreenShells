#pragma once
#include "Unit.h"

class UnitArcherI : public Unit<UnitArcherI>
{
public:
    typedef Unit<UnitArcherI> tBase;

    static const int ATTACK_DAMAGE = 50;
    static const int ATTACK_RANGE = 3;
    static const int HEALTH = 150;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 3;
    static const int WEAPON_COST = 50;
    static const int VIEW_RANGE = 4;
    static const char* UNIT_NAME;

public:

    UnitArcherI(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitArcherI();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static std::shared_ptr<UnitArcherI> Deserialize(boost::property_tree::ptree node);
};