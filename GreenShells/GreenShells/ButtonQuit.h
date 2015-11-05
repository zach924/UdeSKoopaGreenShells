#pragma once
#include "Button.h"
class ButtonQuit : public Button
{
public:
	ButtonQuit(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state);
	~ButtonQuit();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

