#pragma once
#include "Button.h"
class ButtonUnitMove : public Button
{
public:
	ButtonUnitMove(int topLimit, int botLimit, int leftLimit, int rightLimit);
	~ButtonUnitMove();

	void DoAction();

	void LoadTexture();
};

