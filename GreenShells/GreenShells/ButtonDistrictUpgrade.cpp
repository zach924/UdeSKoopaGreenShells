#include <iostream>
#include "ButtonDistrictUpgrade.h"
#include "SelectionManager.h"

ButtonDistrictUpgrade::ButtonDistrictUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonDistrictUpgrade::~ButtonDistrictUpgrade()
{
}

void ButtonDistrictUpgrade::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictUpgrade::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Upgrade_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
