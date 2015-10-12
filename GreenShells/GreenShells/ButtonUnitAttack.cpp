#include <iostream>
#include "ButtonUnitAttack.h"
#include "SelectionManager.h"


ButtonUnitAttack::ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUnitAttack::~ButtonUnitAttack()
{
}

void ButtonUnitAttack::DoAction()
{
	SelectionManager::GetInstance().UnitAttackPressed();
}

void ButtonUnitAttack::LoadTextTexture()
{
	try
	{
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\attack_text.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

