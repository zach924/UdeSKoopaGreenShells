#pragma once
#include "Button.h"

class ButtonUnitAttack : public Button
{
	
public:
	ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
	~ButtonUnitAttack();

	void DoAction();

	void LoadTextTexture();
};

