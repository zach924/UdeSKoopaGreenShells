#pragma once
#include "Button.h"
class ButtonResSelect :
	public Button
{
public:
	ButtonResSelect(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
	~ButtonResSelect();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

