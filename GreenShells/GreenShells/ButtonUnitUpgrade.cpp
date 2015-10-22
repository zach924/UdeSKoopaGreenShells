#include <iostream>
#include "ButtonUnitUpgrade.h"
#include "SelectionManager.h"

ButtonUnitUpgrade::ButtonUnitUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitUpgrade::~ButtonUnitUpgrade()
{
}

void ButtonUnitUpgrade::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitUpgrade::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Upgrade_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
