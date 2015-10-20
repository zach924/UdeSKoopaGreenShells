#include <iostream>
#include "ButtonUnitHeal.h"
#include "SelectionManager.h"

ButtonUnitHeal::ButtonUnitHeal(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonUnitHeal::~ButtonUnitHeal()
{
}

void ButtonUnitHeal::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitHeal::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Heal_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
