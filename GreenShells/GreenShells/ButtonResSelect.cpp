#include <iostream>
#include "ButtonResSelect.h"



ButtonResSelect::ButtonResSelect(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}


ButtonResSelect::~ButtonResSelect()
{
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
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\Yes_text.bmp", rend);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}