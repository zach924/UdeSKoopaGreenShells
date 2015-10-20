#include <iostream>
#include "ButtonGeneralCancel.h"
#include "SelectionManager.h"

ButtonGeneralCancel::ButtonGeneralCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonGeneralCancel::~ButtonGeneralCancel()
{
}

void ButtonGeneralCancel::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonGeneralCancel::LoadTextTexture()
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
