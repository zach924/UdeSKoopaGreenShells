#include <iostream>
#include "ButtonUnitAttack.h"
#include "SelectionManager.h"


ButtonUnitAttack::ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex)
	:Button(sectionOffset, columnIndex, rowIndex)
{
}


ButtonUnitAttack::~ButtonUnitAttack()
{
}

void ButtonUnitAttack::DoAction()
{
	SelectionManager::GetInstance().UnitAttackPressed();
}

void ButtonUnitAttack::LoadTexture()
{
	try
	{
		m_texture.LoadFromFile("..\\Sprite\\Button\\64x64\\UnitAttack.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

