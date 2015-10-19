#pragma once
#include "Unit.h"

class Swordsman : public Unit<Swordsman>
{
public :
	typedef Unit<Swordsman> tBase;

	static int const ATTACK_DAMAGE = 50;
	static int const HEALTH = 100;

private :
	static int const UNIT_TYPE = 0;

public :
	Swordsman(int owner);
	~Swordsman();

	void LoadTexture();

	virtual int GetTypeAsInt();
	virtual void Heal(int health);

	virtual AttackNotification Attack(UnitBase* target);
	virtual AttackNotification Attack(DistrictBase* target);

	static Swordsman* Deserialize(boost::property_tree::ptree node);
};