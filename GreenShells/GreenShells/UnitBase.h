#pragma once

#include "AttackNotification.h" 
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class DistrictBase;
class Texture;

class UnitBase
{
public:
	static const int MIN_ATTACK_RANGE = 1;
	static const int MAX_ATTACK_RANGE = 4; // TODO : Balancing on that
	static const int MELEE_ATTACK_RANGE = 1;

protected:
	int m_health;

private:
	int m_ownerID;
	Position m_position;

	int m_foodCost;
	int m_scienceCost;
	int m_weaponCost;

	int m_attackDamage;
	int m_attackRange;

public:
	UnitBase(int owner, int health, int attackRange, int attackDamage);
	~UnitBase();

	int GetAttackDamage();
	int GetHealth();
	int GetOwnerID();

	virtual int GetTypeAsInt() = 0;

	Position GetPosition();
	void SetPosition(Position pos);
    virtual Texture* GetTexture() = 0;
	virtual void Heal(int health) = 0;

	virtual AttackNotification Attack(UnitBase* target);
	virtual AttackNotification Attack(DistrictBase* target);
	
	AttackNotification ReceiveDamage(int damage); // NEED TO REDEFINE THE RECEIVE DAMAGE IN MELEE UNIT - see UnitSwordsman (you ned exactly the same thing)


	virtual void NotifyNewTurn();

	boost::property_tree::ptree Serialize();
	//static UnitBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);

};