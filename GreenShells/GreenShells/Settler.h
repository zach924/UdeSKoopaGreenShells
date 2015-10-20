#pragma once
#include "Unit.h"

class Settler : public Unit<Settler>
{
public:
	typedef Unit<Settler> tBase;

	static int const ATTACK_DAMAGE = 5;
	static int const HEALTH = 100;

public:
	Settler(int owner);
	~Settler();

	void LoadTexture();

	virtual void Heal(int health);

	virtual AttackNotification Attack(UnitBase* target);
	virtual AttackNotification Attack(DistrictBase* target);

	virtual  boost::property_tree::ptree Serialize();
};