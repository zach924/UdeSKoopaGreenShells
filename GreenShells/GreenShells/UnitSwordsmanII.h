#pragma once
#include "Unit.h"

class UnitSwordsmanII : public Unit<UnitSwordsmanII>
{
public:
    typedef Unit<UnitSwordsmanII> tBase;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 250;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 1;
    static const int WEAPON_COST = 100;
    static const int VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanII(int owner, bool hasBonusActionPoint = false);
    ~UnitSwordsmanII();
    virtual std::shared_ptr<UnitBase> Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    static std::shared_ptr<UnitSwordsmanII> Deserialize(boost::property_tree::ptree node);
};

