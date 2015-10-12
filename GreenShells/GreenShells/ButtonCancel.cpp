#include <iostream>
#include "ButtonCancel.h"
#include "SelectionManager.h"

ButtonCancel::ButtonCancel(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonCancel::~ButtonCancel()
{
}

void ButtonCancel::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonCancel::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Cancel_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
