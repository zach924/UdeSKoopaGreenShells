#pragma once
#include "Button.h"
class ButtonRes : public Button
{
public:
	ButtonRes(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state);
	~ButtonRes();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

