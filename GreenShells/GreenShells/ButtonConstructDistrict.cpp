#include <iostream>
#include "ButtonConstructDistrict.h"
#include "YesNoPopUp.h"
#include "GameWindow.h"
#include "SelectionManager.h"
#include "DistrictFarm.h"

ButtonConstructDistrict::ButtonConstructDistrict(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonConstructDistrict::~ButtonConstructDistrict()
{
}

void ButtonConstructDistrict::DoAction()
{
	// TODO : add the popup window for selection, and move that line in popup window
	SelectionManager::GetInstance().CreateDistrictPressed(DistrictFarm::DISTRICT_TYPE);
}

void ButtonConstructDistrict::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\ConstructDistrict_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
