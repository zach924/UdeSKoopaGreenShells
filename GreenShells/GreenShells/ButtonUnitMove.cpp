#include <iostream>
#include "ButtonUnitMove.h"
#include "SelectionManager.h"


ButtonUnitMove::ButtonUnitMove(int sectionOffset, int columnIndex, int rowIndex)
	:Button(sectionOffset, columnIndex, rowIndex)
{
}


ButtonUnitMove::~ButtonUnitMove()
{
}

void ButtonUnitMove::DoAction()
{
	SelectionManager::GetInstance().UnitMovePressed();
}

void ButtonUnitMove::LoadTexture()
{
	try
	{
		m_texture.LoadFromFile("..\\Sprite\\Button\\64x64\\UnitMove.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}