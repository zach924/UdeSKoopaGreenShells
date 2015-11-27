#pragma once
#include "Unit.h"

class UnitSwordsmanIII : public Unit<UnitSwordsmanIII>
{
public:
    typedef Unit<UnitSwordsmanIII> tBase;

    static int const ATTACK_DAMAGE = 100;
    static int const HEALTH = 300;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 2;
    static int const UNIT_TIER = 3;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanIII(int owner);
    ~UnitSwordsmanIII();
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

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitSwordsmanIII> Deserialize(boost::property_tree::ptree node);
};