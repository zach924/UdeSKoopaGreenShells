#include <iostream>
#include "ButtonUnitHeal.h"
#include "SelectionManager.h"

ButtonUnitHeal::ButtonUnitHeal(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitHeal::~ButtonUnitHeal()
{
}

void ButtonUnitHeal::DoAction()
{
    SelectionManager::GetInstance().UnitHeal();
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