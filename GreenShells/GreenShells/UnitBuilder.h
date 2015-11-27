#pragma once
#include "Unit.h"

class UnitBuilder : public Unit<UnitBuilder>
{
public:
    typedef Unit<UnitBuilder> tBase;

    static int const ATTACK_DAMAGE = 25;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 200;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 13;
    static int const UNIT_TIER = 1;
    static int const VIEW_RANGE = 5;
    static const char* UNIT_NAME;

    UnitBuilder(int owner);
    virtual ~UnitBuilder();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual int GetUnitTier();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);
    virtual void Update(Map* map);

    static std::shared_ptr<UnitBuilder> Deserialize(boost::property_tree::ptree node);
};



