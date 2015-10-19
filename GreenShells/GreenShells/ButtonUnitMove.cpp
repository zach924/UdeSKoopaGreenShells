#include <iostream>
#include "ButtonUnitMove.h"
#include "SelectionManager.h"


ButtonUnitMove::ButtonUnitMove(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUnitMove::~ButtonUnitMove()
{
}

void ButtonUnitMove::DoAction()
{
	SelectionManager::GetInstance().UnitMovePressed();
}

void ButtonUnitMove::LoadTextTexture(SDL_Renderer* rend)
{
	try
	{
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\Move_text.bmp", rend);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}