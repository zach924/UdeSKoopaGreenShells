#pragma once
#include "Unit.h"

class UnitSwordsmanI : public Unit<UnitSwordsmanI>
{
public:
    typedef Unit<UnitSwordsmanI> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const HEALTH = 200;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 0;
    static int const UNIT_TIER = 1;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanI(int owner);
    ~UnitSwordsmanI();
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
    virtual void Upgrade(Map* map);

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitSwordsmanI> Deserialize(boost::property_tree::ptree node);
};