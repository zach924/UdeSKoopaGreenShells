#include <iostream>
#include "ButtonSell.h"
#include "SelectionManager.h"

ButtonSell::ButtonSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonSell::~ButtonSell()
{
}

void ButtonSell::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonSell::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Sell_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
