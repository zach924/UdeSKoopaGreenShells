#include <iostream>
#include "ButtonYes.h"

ButtonYes::ButtonYes(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonYes::~ButtonYes()
{
}

void ButtonYes::DoAction()
{
    // Do nothing. We Use it only for the isInside method
    return;
}

void ButtonYes::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Yes_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}