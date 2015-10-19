#pragma once
#include "Unit.h"

class Archer : public Unit<Archer>
{
public:
	typedef Unit<Archer> tBase;

	static int const ATTACK_DAMAGE = 50;
	static int const HEALTH = 100;

	static int const UNIT_TYPE = 1;


public:
	Archer(int owner);
	~Archer();

	void LoadTexture();

	virtual int GetTypeAsInt();
	virtual void Heal(int health);

	virtual  boost::property_tree::ptree Serialize();
};