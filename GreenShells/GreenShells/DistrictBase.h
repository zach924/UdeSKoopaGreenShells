#pragma once
#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class DistrictBase
{
public :
	static const int NORMAL_DISTRICT_ATTACK_DMG = 0;

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
	DistrictBase(int owner, int health, int attackDamage);
	~DistrictBase();

	int GetAttackDamage();
	int GetHealth();
	int GetOwnerID();

	Position GetPosition();
	void SetPosition(Position pos);

	virtual void Repair(int repairValue) = 0;
	virtual AttackNotification ReceiveDamage(int damage);


	virtual void NotifyNewTurn();

	//virtual boost::property_tree::ptree Serialize();
};