#include <iostream>
#include "ButtonDistrictRepair.h"
#include "SelectionManager.h"

ButtonDistrictRepair::ButtonDistrictRepair(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonDistrictRepair::~ButtonDistrictRepair()
{
}

void ButtonDistrictRepair::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictRepair::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Repair_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}