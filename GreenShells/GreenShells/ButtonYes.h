#pragma once
#include "Button.h"
class ButtonYes :
	public Button
{
public:
	ButtonYes(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
	~ButtonYes();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

