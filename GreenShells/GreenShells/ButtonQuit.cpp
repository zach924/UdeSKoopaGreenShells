#include <iostream>
#include "ButtonQuit.h"
#include "GameWindow.h"

ButtonQuit::ButtonQuit(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}


ButtonQuit::~ButtonQuit()
{
}

void ButtonQuit::DoAction()
{
	GameWindow::GetInstance().RequestQuit();
}

void ButtonQuit::LoadTextTexture(SDL_Renderer* rend)
{
	try
	{
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\No_text.bmp", rend);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}
