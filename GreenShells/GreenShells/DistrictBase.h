#pragma once
#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class Texture;

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
	virtual ~DistrictBase();

	virtual DistrictBase* Clone() = 0;

	int GetAttackDamage();
	int GetHealth();
	int GetOwnerID();
    virtual Texture* GetTexture() = 0;
	Position GetPosition();
	void SetPosition(Position pos);
	virtual int GetTypeAsInt() = 0;

	virtual void Repair(int repairValue) = 0;
	virtual AttackNotification ReceiveDamage(int damage);


	virtual void NotifyNewTurn();

	boost::property_tree::ptree Serialize();
};