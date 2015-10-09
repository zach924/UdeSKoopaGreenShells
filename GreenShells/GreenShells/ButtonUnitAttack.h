#pragma once
#include "Button.h"

class ButtonUnitAttack : public Button
{
	
public:
	ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex);
	~ButtonUnitAttack();

	void DoAction();

	void LoadTexture();
};

