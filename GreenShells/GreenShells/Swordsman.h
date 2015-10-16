#pragma once
#include "Unit.h"

class Swordsman : public Unit<Swordsman>
{
public :
	typedef Unit<Swordsman> tBase;

	static int const ATTACK_DAMAGE = 50;
	static int const HEALTH = 100;

public :
	Swordsman(int owner);
	~Swordsman();

	void LoadTexture();

	virtual void Heal(int health);

	virtual AttackNotification Attack(UnitBase* target);
	virtual AttackNotification Attack(DistrictBase* target);

	virtual  boost::property_tree::ptree Serialize();
};