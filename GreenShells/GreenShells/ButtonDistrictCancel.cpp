#include <iostream>
#include "ButtonDistrictCancel.h"
#include "SelectionManager.h"

ButtonDistrictCancel::ButtonDistrictCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonDistrictCancel::~ButtonDistrictCancel()
{
}

void ButtonDistrictCancel::DoAction()
{
    SelectionManager::GetInstance().Cancel();
}

void ButtonDistrictCancel::LoadTextTexture(SDL_Renderer* rend)
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