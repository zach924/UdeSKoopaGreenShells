#include <iostream>
#include "ButtonConstructDistrict.h"
#include "SelectionManager.h"
#include "DistrictFarm.h"
#include "ConstructDistrictPopUp.h"
#include "GameWindow.h"

ButtonConstructDistrict::ButtonConstructDistrict(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonConstructDistrict::~ButtonConstructDistrict()
{
}

void ButtonConstructDistrict::DoAction()
{
    ConstructDistrictPopUp* popUp = new ConstructDistrictPopUp("", 500, 590);

    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonConstructDistrict::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Resources\\Sprite\\Button\\ConstructDistrict_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}