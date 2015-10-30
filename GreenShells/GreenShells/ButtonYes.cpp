#include <iostream>
#include "ButtonYes.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

ButtonYes::ButtonYes(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}


ButtonYes::~ButtonYes()
{
}

void ButtonYes::DoAction()
{
	// Do nothing. We Use it only for the isInside method
	return;
}

void ButtonYes::LoadTextTexture(SDL_Renderer* rend)
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