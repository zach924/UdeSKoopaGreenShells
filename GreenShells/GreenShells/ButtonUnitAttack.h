#pragma once
#include "Button.h"

class ButtonUnitAttack : public Button
{
	
public:
	ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
	~ButtonUnitAttack();

	void DoAction();

	void LoadTextTexture();
};

