#include <iostream>
#include "ButtonUnitUpgrade.h"
#include "SelectionManager.h"

ButtonUnitUpgrade::ButtonUnitUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonUnitUpgrade::~ButtonUnitUpgrade()
{
}

void ButtonUnitUpgrade::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitUpgrade::LoadTextTexture()
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
