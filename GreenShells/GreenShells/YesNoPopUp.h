#pragma once
#include "PopUpWindow.h"
#include "ButtonYes.h"
#include "ButtonNo.h"

class YesNoPopUp :
	public PopUpWindow
{
	ButtonYes* m_yesButton;

	std::function<void()> m_yesFunction;

	ButtonNo* m_noButton;

public:

	YesNoPopUp(const char* windowName, int width, int height, std::function<void()> yesFunction);
	~YesNoPopUp();

	void ShowWindow(SDL_Renderer* rend);


	bool handleEvent(SDL_Event& e);
};

