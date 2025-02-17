#include <iostream>
#include "ButtonUnitCancel.h"
#include "SelectionManager.h"

ButtonUnitCancel::ButtonUnitCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitCancel::~ButtonUnitCancel()
{
}

void ButtonUnitCancel::DoAction()
{
    SelectionManager::GetInstance().Cancel();
}

void ButtonUnitCancel::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Resources\\Sprite\\Button\\Cancel_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}