#pragma once
#include <string>
#include "Button.h"
#include "GameWindow.h"

class ButtonResSelect :
	public Button
{
private:
    std::string m_resText;
    ScreenResolution m_res;
public:
	ButtonResSelect(std::string resolutionText, int posX, int posY, int width, int height, ScreenResolution res, ButtonState = ButtonState::Disabled);
	~ButtonResSelect();

	void DoAction();

	void LoadTextTexture(SDL_Renderer* rend = nullptr);

    ScreenResolution& GetRes();
};

