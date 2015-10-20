#include <iostream>
#include "ButtonUnitMove.h"
#include "SelectionManager.h"


ButtonUnitMove::ButtonUnitMove(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonUnitMove::~ButtonUnitMove()
{
}

void ButtonUnitMove::DoAction()
{
	SelectionManager::GetInstance().UnitMovePressed();
}

void ButtonUnitMove::LoadTextTexture()
{
	try
	{
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\Move_text.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}