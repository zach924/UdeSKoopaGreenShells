#include <iostream>
#include "ButtonResSelect.h"


ButtonResSelect::ButtonResSelect(std::string resolutionText, int posX, int posY, int width, int height, ScreenResolution res, ButtonState state)
	:Button(posX, posY, width, height, state)
    , m_resText(resolutionText)
    , m_res(res)
{
}


ButtonResSelect::~ButtonResSelect()
{
    std::cout << "BTN DELETE" << std::endl;
}

void ButtonResSelect::DoAction()
{
	// Do nothing. We Use it only for the isInside method
	return;
}

void ButtonResSelect::LoadTextTexture(SDL_Renderer* rend)
{
	try
	{
        std::cout << m_resText << std::endl;
        m_textTexture.CreateFromText(m_resText, nullptr, rend);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

ScreenResolution & ButtonResSelect::GetRes()
{
    return m_res;
}
