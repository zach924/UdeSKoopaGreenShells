#include <iostream>
#include "ButtonUnitHeal.h"
#include "SelectionManager.h"

ButtonUnitHeal::ButtonUnitHeal(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUnitHeal::~ButtonUnitHeal()
{
}

void ButtonUnitHeal::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitHeal::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Heal_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
