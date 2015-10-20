#include <iostream>
#include "ButtonDiplomacy.h"
#include "SelectionManager.h"

ButtonDiplomacy::ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonDiplomacy::~ButtonDiplomacy()
{
}

void ButtonDiplomacy::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDiplomacy::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Diplomacy_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
