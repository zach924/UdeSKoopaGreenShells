#pragma once
#include "Button.h"

class ButtonUnitAttack : public Button
{
	
public:
	ButtonUnitAttack(int topLimit, int botLimit, int leftLimit, int rightLimit);
	~ButtonUnitAttack();

	void DoAction();

	void LoadTexture();
};

