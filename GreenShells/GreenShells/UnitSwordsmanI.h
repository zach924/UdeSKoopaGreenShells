#pragma once
#include "Unit.h"

class UnitSwordsmanI : public Unit<UnitSwordsmanI>
{
public:
    typedef Unit<UnitSwordsmanI> tBase;

    static const int ATTACK_DAMAGE = 50;
    static const int HEALTH = 200;
    static const int ACTION_POINTS = 2;
    static const int UNIT_TYPE = 0;
    static const int WEAPON_COST = 50;
    static const int VIEW_RANGE = 3;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanI(int owner, bool hasBonusActionPoint = false);
    ~UnitSwordsmanI();
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

    static std::shared_ptr<UnitSwordsmanI> Deserialize(boost::property_tree::ptree node);
};