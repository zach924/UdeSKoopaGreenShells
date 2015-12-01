#pragma once

#include <memory>
#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class DistrictBase;
class Texture;
class Map;

class UnitBase
{
    int m_foodCost;
    int m_weaponCost;
    int m_attackDamage;
    int m_attackRange;
    int m_viewRange;
    int m_typeAsInt;
    int m_maxHealth;
    int m_defaultActionPoints;
    int m_ownerID;
    int m_upgradeType;
    std::string m_name;
    Position m_position;

protected:
    int m_health;
    int m_actionPointsLeft;

public:
    static const int NO_FOOD_COST = -1;
    static const int NO_UPGRADE = -1;
    static const int MELEE_ATTACK_RANGE = 1;

    UnitBase(int owner, int health, int actionPoints, int attackRange, int attackDamage, int viewRange, const char* name, int typeAsInt, int weaponCost, int foodCost, int upgradeType);
    virtual ~UnitBase();
    virtual std::shared_ptr<UnitBase> Clone() = 0;
    virtual Texture* GetTexture() = 0;
    virtual bool CanUpgrade() = 0;
    virtual AttackNotification Attack(std::shared_ptr<UnitBase> target);
    virtual AttackNotification Attack(std::shared_ptr<DistrictBase> target);

    int GetActionPointsRemaining();
    int GetAttackDamage();
    int GetAttackRange();
    int GetHealth();
    int GetOwnerID();
    int GetUpgradeType();
    int GetMaxHealth();
    int GetTypeAsInt();
    int GetViewRange();
    int GetWeaponCost();
    int GetFoodCost();
    const char* GetName();
    Position GetPosition();
    void UseActionPoints(int points);
    void SetPosition(Position pos);
    void Heal(int health);
    void NotifyNewTurn(int turn);
    AttackNotification ReceiveDamage(int damage);
    boost::property_tree::ptree Serialize();
};