#include <iostream>
#include "ButtonGeneralCancel.h"
#include "SelectionManager.h"

ButtonGeneralCancel::ButtonGeneralCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonGeneralCancel::~ButtonGeneralCancel()
{
}

void ButtonGeneralCancel::DoAction()
{
    SelectionManager::GetInstance().Cancel();
}

void ButtonGeneralCancel::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Cancel_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}