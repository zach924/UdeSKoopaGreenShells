#include <iostream>
#include "ButtonConstructDistrict.h"
#include "SelectionManager.h"

ButtonConstructDistrict::ButtonConstructDistrict(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonConstructDistrict::~ButtonConstructDistrict()
{
}

void ButtonConstructDistrict::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonConstructDistrict::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\ConstructDistrict_text.bmp");
        std::cout << "Loading TEXT_BUTTON_CONSTRUC_D" << std::endl;
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}