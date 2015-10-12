#pragma once
#include "UnitMelee.h"

class Swordsman : public Unit<Swordsman>
{
public :
	typedef Unit<Swordsman> tBase;

	int const ATTACK_DAMAGE = 50;
	int const HEALTH = 100;


public :
	Swordsman(int owner);
	~Swordsman();

	void LoadTexture();
};