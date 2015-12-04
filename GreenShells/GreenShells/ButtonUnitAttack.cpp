#include <iostream>
#include "ButtonUnitAttack.h"
#include "SelectionManager.h"

ButtonUnitAttack::ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitAttack::~ButtonUnitAttack()
{
}

void ButtonUnitAttack::DoAction()
{
    SelectionManager::GetInstance().UnitAttackPressed();
}

void ButtonUnitAttack::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Ressources\\Sprite\\Button\\attack_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}