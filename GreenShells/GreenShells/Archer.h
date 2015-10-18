#pragma once
#include "Unit.h"

class Archer : public Unit<Archer>
{
public:
	typedef Unit<Archer> tBase;

	static int const ATTACK_DAMAGE = 50;
	static int const HEALTH = 100;


public:
	Archer(int owner);
	~Archer();

	void LoadTexture();

	virtual void Heal(int health);

	virtual  boost::property_tree::ptree Serialize();
};