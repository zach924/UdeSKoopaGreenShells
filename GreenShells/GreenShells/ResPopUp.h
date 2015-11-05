#pragma once
#include "PopUpWindow.h"
#include "ButtonResSelect.h"

class ResPopUp :
	public PopUpWindow
{
private:
	ButtonResSelect* m_800_600;
	ButtonResSelect* m_1280_720;
	ButtonResSelect* m_1600_900;
	ButtonResSelect* m_1600_1024;
	ButtonResSelect* m_1920_1080;
	ButtonResSelect* m_1920_1080_FullScreen;

	void RenderButton(ButtonResSelect* butt, SDL_Renderer* rend);
public:
	ResPopUp(const char* windowName, int width, int height);
	~ResPopUp();

	void ShowWindow(SDL_Renderer* rend);

	bool handleEvent(SDL_Event& e);

};

