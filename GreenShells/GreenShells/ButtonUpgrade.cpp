#include <iostream>
#include "ButtonUpgrade.h"
#include "SelectionManager.h"

ButtonUpgrade::ButtonUpgrade(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUpgrade::~ButtonUpgrade()
{
}

void ButtonUpgrade::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUpgrade::LoadTextTexture()
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
