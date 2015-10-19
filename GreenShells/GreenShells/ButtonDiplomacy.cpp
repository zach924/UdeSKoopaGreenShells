#include <iostream>
#include "ButtonDiplomacy.h"
#include "SelectionManager.h"

ButtonDiplomacy::ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonDiplomacy::~ButtonDiplomacy()
{
}

void ButtonDiplomacy::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDiplomacy::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Diplomacy_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
