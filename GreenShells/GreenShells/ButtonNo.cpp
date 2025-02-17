#include <iostream>
#include "ButtonNo.h"

ButtonNo::ButtonNo(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonNo::~ButtonNo()
{
}

void ButtonNo::DoAction()
{
    // Do nothing. We Use it only for the isInside method
    return;
}

void ButtonNo::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Resources\\Sprite\\Button\\No_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}