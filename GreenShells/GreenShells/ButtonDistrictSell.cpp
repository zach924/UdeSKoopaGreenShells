#include <iostream>
#include "ButtonDistrictSell.h"
#include "SelectionManager.h"

ButtonDistrictSell::ButtonDistrictSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonDistrictSell::~ButtonDistrictSell()
{
}

void ButtonDistrictSell::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictSell::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Sell_text.bmp",rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
