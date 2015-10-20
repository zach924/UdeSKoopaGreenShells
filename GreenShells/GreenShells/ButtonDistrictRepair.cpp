#include <iostream>
#include "ButtonDistrictRepair.h"
#include "SelectionManager.h"

ButtonDistrictRepair::ButtonDistrictRepair(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonDistrictRepair::~ButtonDistrictRepair()
{
}

void ButtonDistrictRepair::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictRepair::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Repair_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
