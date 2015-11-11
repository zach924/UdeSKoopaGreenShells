#pragma once
#include "Button.h"
class ButtonQuit : public Button
{
public:
	ButtonQuit(int posX, int posY, int width, int height, ButtonState state);
	~ButtonQuit();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

