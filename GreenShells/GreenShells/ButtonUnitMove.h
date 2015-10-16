#pragma once
#include "Button.h"
class ButtonUnitMove : public Button
{
public:
	ButtonUnitMove(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
	~ButtonUnitMove();

	void DoAction();

	void LoadTextTexture();
};

