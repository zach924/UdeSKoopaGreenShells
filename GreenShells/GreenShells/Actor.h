#pragma once
#include "Position.h"
#include "Player.h"
#include "Ptree_ForwardDeclaration.h"

struct AttackNotification 
{
	bool AttackerIsDead;
	bool TargetIsDead;
	bool CanMove;
	int RiposteDamage;

	AttackNotification(int damage, bool targetDead, bool canMove) : 
		RiposteDamage(damage), 
		TargetIsDead(targetDead),
		AttackerIsDead(false),
		CanMove(canMove)
	{}
};

class Actor
{
protected:
	int m_ownerID;
	int m_health;

private:
    Position m_position;

    int m_foodCost;
    int m_scienceCost;
    int m_weaponCost;

    double m_foodRatioBonus;
    double m_scienceRatioBonus;
    double m_weaponRatioBonus;

	int m_attackDamage;

public:
	Actor(int ownerID, Position position = Position(-1,-1));
    ~Actor();

	void SetOwnerID(int ID);
	int GetOwnerID();

	int GetHealth();

	int GetAttackDamage();
	void SetAttackDamage(int damage);

	virtual AttackNotification ReceiveDamage(int damage);

	virtual void NotifyNewTurn() = 0;
	virtual boost::property_tree::ptree Serialize() = 0;

};

