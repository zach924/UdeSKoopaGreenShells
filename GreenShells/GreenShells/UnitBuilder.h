#pragma once
#include "Unit.h"

class UnitBuilder : public Unit<UnitBuilder>
{
public:
    typedef Unit<UnitBuilder> tBase;

    static const int WEAPON_COST = 0;
    static const int FOOD_COST = 75;
    static const int ATTACK_DAMAGE = 25;
    static const int ATTACK_RANGE = 1;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 13;
    static const int VIEW_RANGE = 5;
    static const char* UNIT_NAME;

    UnitBuilder(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitBuilder();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static std::shared_ptr<UnitBuilder> Deserialize(boost::property_tree::ptree node);
};



