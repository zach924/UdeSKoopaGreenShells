#pragma once

#include <memory>
#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"
#include <string>

class Texture;
class Map;

class DistrictBase
{
    int m_ownerID;
    int m_maxHealth;
    int m_weaponYield;
    int m_foodYield;
    int m_scienceYield;
    int m_viewRange;
    int m_typeAsInt;
    int m_foodCost;
    double m_foodBonus;
    double m_scienceBonus;
    double m_weaponBonus;
    int m_attackDamage;
    int m_upgradeType;
    std::string m_name;
    Position m_position;

protected:
    static const int NO_UPGRADE = -1;
    int m_actionPointsLeft;
    int m_health;

public:
    DistrictBase(int owner, int health, int attackDamage, int viewRange, const char* name, int typeAsInt, int foodCost, int weaponYield, int foodYield, int scienceYield, int upgradeType, double foodBonus, double scienceBonus, double weaponBonus);
    virtual ~DistrictBase();

    virtual void Repair(int repairValue);
    virtual void ChangeOwner(int newOwner);
    virtual AttackNotification ReceiveDamage(int damage);
    virtual bool CanUpgrade() = 0;
    virtual Texture* GetTexture() = 0;
    virtual std::shared_ptr<DistrictBase> Clone() = 0;

    int GetFoodCost();
    int GetActionPointsRemaining();
    int GetAttackDamage();
    int GetHealth();
    int GetOwnerID();
    int GetTypeAsInt();
    int GetViewRange();
    int GetMaxHealth();
    int GetUpgradeType();
    int GetWeaponYield();
    int GetScienceYield();
    int GetFoodYield();
    double GetFoodBonus();
    double GetScienceBonus();
    double GetWeaponBonus();
    const char* GetName();
    Position GetPosition();
    void NotifyNewTurn(int turn);
    void SetPosition(Position pos);
    boost::property_tree::ptree Serialize();
};