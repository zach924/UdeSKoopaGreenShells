#pragma once
#include "Unit.h"

class UnitCannon : public Unit<UnitCannon>
{
public:
    typedef Unit<UnitCannon> tBase;

    static const int ATTACK_DAMAGE = 200;
    static const int ATTACK_RANGE = 4;
    static const int HEALTH = 150;
    static const int ACTION_POINTS = 1;
    static const int UNIT_TYPE = 10;
    static const int WEAPON_COST = 450;
    static const int VIEW_RANGE = 5;
    static const char* UNIT_NAME;

    UnitCannon(int owner, bool hasBonusActionPoint = false);
    virtual ~UnitCannon();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    static std::shared_ptr<UnitCannon> Deserialize(boost::property_tree::ptree node);
};

