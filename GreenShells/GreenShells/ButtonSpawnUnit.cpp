#include <iostream>
#include "ButtonSpawnUnit.h"
#include "SelectionManager.h"
#include "UnitSwordsman.h"

ButtonSpawnUnit::ButtonSpawnUnit(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonSpawnUnit::~ButtonSpawnUnit()
{
}

void ButtonSpawnUnit::DoAction()
{
    // TODO : add the popup window for selection, and move that line in popup window
    SelectionManager::GetInstance().CreateUnitPressed(UnitSwordsman::UNIT_TYPE);
}

void ButtonSpawnUnit::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\SpawnUnit_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}