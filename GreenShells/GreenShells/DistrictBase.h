#pragma once
#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class Texture;

class DistrictBase
{
public:

protected:
    int m_ownerID;
    int m_health;

private:
    Position m_position;

    int m_foodCost;

    int m_foodRatioBonus;
    int m_scienceBonus;
    int m_weaponBonus;

    int m_attackDamage;

    int m_actionPointsLeft;

public:
    DistrictBase(int owner, int health, int attackDamage, int foodCost, int foodBonus, int scienceBonus, int weaponBonus);
    virtual ~DistrictBase();

    virtual DistrictBase* Clone() = 0;

    virtual void ChangeOwner(int newOwner);
    int GetActionPointsRemaining();
    int GetAttackDamage();
    int GetHealth();
    int GetOwnerID();
    virtual Texture* GetTexture() = 0;
    Position GetPosition();
    void SetPosition(Position pos);
    virtual int GetMaxHealth() = 0;
    virtual const char* GetName() = 0;
    virtual int GetTypeAsInt() = 0;
    virtual bool CanUpgrade() = 0;

    virtual void Repair(int repairValue) = 0;
    virtual AttackNotification ReceiveDamage(int damage);

    virtual void NotifyNewTurn(int turn);

    boost::property_tree::ptree Serialize();
};