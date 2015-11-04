#include <iostream>
#include "ButtonDistrictUpgrade.h"
#include "SelectionManager.h"

ButtonDistrictUpgrade::ButtonDistrictUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonDistrictUpgrade::~ButtonDistrictUpgrade()
{
}

void ButtonDistrictUpgrade::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictUpgrade::LoadTextTexture(SDL_Renderer* rend)
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