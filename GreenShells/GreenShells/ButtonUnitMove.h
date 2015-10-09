#pragma once
#include "Button.h"
class ButtonUnitMove : public Button
{
public:
	ButtonUnitMove(int sectionOffset, int columnIndex, int rowIndex);
	~ButtonUnitMove();

	void DoAction();

	void LoadTexture();
};

